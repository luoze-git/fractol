#include "fracto_header.h"

// set the initial view for the fractal. Now only for Mandelbrot
void	set_view(t_context *ctx)
{
	if (ctx->fractal_type == FRACTAL_JULIA)
	{
		ctx->view.re_min = -2.0;
		ctx->view.re_max = 2.0;
		ctx->view.im_min = -2.0;
		ctx->view.im_max = 2.0;
	}
	if (ctx->fractal_type == FRACTAL_MANDELBROT || ctx->fractal_type == FRACTAL_TRICORN)
	{
		ctx->view.re_min = -2.0;
		ctx->view.re_max = 1.0;
		ctx->view.im_min = -1.5;
		ctx->view.im_max = 1.5;
	}
}

void	init_hooks(t_context *ctx)
{
	mlx_key_hook(ctx->mlx, &handle_key_callback, ctx);
	mlx_scroll_hook(ctx->mlx, &handle_scroll_callback, ctx);
}

void	init_context(t_context *ctx)
{
	ctx->mlx = mlx_init(WIDTH, HEIGHT, "fractol", false);
	if (!ctx->mlx)
		exit(EXIT_FAILURE);
	ctx->img = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	if (!ctx->img)
	{
		mlx_terminate(ctx->mlx);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(ctx->mlx, ctx->img, 0, 0) < 0)
	{
		mlx_delete_image(ctx->mlx, ctx->img);
		mlx_terminate(ctx->mlx);
		exit(EXIT_FAILURE);
	}
	ctx->max_iter = 100;
	init_hooks(ctx);
	set_view(ctx);
}
