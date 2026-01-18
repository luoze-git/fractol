/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:11:03 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/18 14:11:04 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fracto_header.h"

static void	zoom_view(t_view *v, double cx, double cy, double factor)
{
	double	width;
	double	height;

	width = (v->re_max - v->re_min) * factor;
	height = (v->im_max - v->im_min) * factor;
	v->re_min = cx - width / 2.0;
	v->re_max = cx + width / 2.0;
	v->im_min = cy - height / 2.0;
	v->im_max = cy + height / 2.0;
}

static void	apply_pan(t_context *ctx, keys_t key)
{
	double	width;
	double	height;
	double	dx;
	double	dy;

	width = ctx->view.re_max - ctx->view.re_min;
	height = ctx->view.im_max - ctx->view.im_min;
	dx = 0.0;
	dy = 0.0;
	if (key == MLX_KEY_LEFT)
		dx = -0.05 * width;
	else if (key == MLX_KEY_RIGHT)
		dx = 0.05 * width;
	else if (key == MLX_KEY_UP)
		dy = 0.05 * height;
	else if (key == MLX_KEY_DOWN)
		dy = -0.05 * height;
	else
		return ;
	ctx->view.re_min += dx;
	ctx->view.re_max += dx;
	ctx->view.im_min += dy;
	ctx->view.im_max += dy;
	ctx->needs_rendering = 1;
}

void	handle_key_callback(mlx_key_data_t key, void *param)
{
	t_context	*ctx;

	ctx = param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(ctx->mlx);
	if (key.action != MLX_PRESS && key.action != MLX_REPEAT)
		return ;
	apply_pan(ctx, key.key);
}

void	handle_scroll_callback(double xdelta, double ydelta, void *param)
{
	t_context	*ctx;
	t_complex	c;
	int32_t		mx;
	int32_t		my;
	double		factor;

	(void)xdelta;
	ctx = param;
	if (ydelta > 0)
		factor = 0.8;
	else if (ydelta < 0)
		factor = 1.2;
	else
		return ;
	mlx_get_mouse_pos(ctx->mlx, &mx, &my);
	pixel_to_complex(ctx, mx, my, &c);
	zoom_view(&(ctx->view), c.r, c.i, factor);
	ctx->needs_rendering = 1;
}

void	loop_callback(void *param)
{
	t_context	*ctx;

	ctx = param;
	if (!ctx->needs_rendering)
		return ;
	rendering_loop(ctx);
	ctx->needs_rendering = 0;
}
