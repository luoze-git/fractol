#include "fracto_header.h"

void handle_key_callback(mlx_key_data_t key, void *param)
{
	t_context *ctx;

	ctx = param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(ctx->mlx);
}

void handle_scroll_callback(double xdelta, double ydelta, void *param)
{
	t_context *ctx;
	t_complex c;
	int32_t mx;
	int32_t my;
	double factor;

	(void)xdelta;
	ctx = param;
	if (ydelta > 0)
		factor = 0.95;
	else if (ydelta < 0)
		factor = 1.05;
	else
		return;
	mlx_get_mouse_pos(ctx->mlx, &mx, &my);
	pixel_to_complex(ctx, mx, my, &c);
	zoom_view(&ctx->view, c.r, c.i, factor);
	iterate_all_pixels(ctx);
}
