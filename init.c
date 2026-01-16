#include "fracto_header.h"

void	set_mlx_and_win(t_context *ctx)
{
	ctx->mlx = mlx_init();
	ctx->win = mlx_new_window(ctx->mlx, 500, 500, "Fractol42");
}
void	set_img(t_context *ctx)
{
	ctx->img.img = mlx_new_image(ctx->mlx, 500, 500);
	ctx->img.addr_pix = mlx_get_data_addr(ctx->img.img, &ctx->img.bpp_bits,
			&ctx->img.line_len_bytes, &ctx->img.endian_dummy);
}

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
	set_mlx_and_win(ctx);
	set_img(ctx);
	set_view(ctx);
	ctx->max_iter = 100;
}
