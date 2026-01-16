#include "fracto_header.h"
#include "MLX42.h"

// set the initial view for the fractal. Now only for Mandelbrot
void	set_view(t_context *ctx)
{
	ctx->view.x_min = -2.0;
	ctx->view.x_max = 1.0;
	ctx->view.y_min = -1.5;
	ctx->view.y_max = 1.5;
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
}
