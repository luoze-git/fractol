/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:11:12 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/18 14:11:13 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fracto_header.h"

static void	fatal_mlx(const char *context, mlx_errno_t err)
{
	ft_putstr_fd("mlx error: ", 2);
	ft_putstr_fd(context, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(mlx_strerror(err), 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

// set the initial view for the fractal. Now only for Mandelbrot
static void	set_view(t_context *ctx)
{
	if (ctx->fractal_type == FRACTAL_JULIA)
	{
		ctx->view.re_min = -2.0;
		ctx->view.re_max = 2.0;
		ctx->view.im_min = -2.0;
		ctx->view.im_max = 2.0;
	}
	if (ctx->fractal_type == FRACTAL_MANDELBROT
		|| ctx->fractal_type == FRACTAL_TRICORN)
	{
		ctx->view.re_min = -2.0;
		ctx->view.re_max = 1.0;
		ctx->view.im_min = -1.5;
		ctx->view.im_max = 1.5;
	}
}

void	init_hooks(t_context *ctx)
{
	mlx_key_hook(ctx->mlx, handle_key_callback, ctx);
	mlx_scroll_hook(ctx->mlx, handle_scroll_callback, ctx);
	mlx_loop_hook(ctx->mlx, loop_callback, ctx);
}

void	init_context(t_context *ctx)
{
	mlx_errno_t	err;

	ctx->mlx = mlx_init(WIDTH, HEIGHT, "fractol", false);
	if (!ctx->mlx)
		fatal_mlx("mlx_init", mlx_get_errno());
	ctx->img = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	if (!ctx->img)
	{
		err = mlx_get_errno();
		mlx_terminate(ctx->mlx);
		fatal_mlx("mlx_new_image", err);
	}
	if (mlx_image_to_window(ctx->mlx, ctx->img, 0, 0) < 0)
	{
		err = mlx_get_errno();
		mlx_delete_image(ctx->mlx, ctx->img);
		mlx_terminate(ctx->mlx);
		fatal_mlx("mlx_image_to_window", err);
	}
	ctx->needs_rendering = 0;
	ctx->max_iter = 100;
	init_hooks(ctx);
	set_view(ctx);
}
