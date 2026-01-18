#include "fracto_header.h"
#include <math.h>

/// @brief increase contrast for depth at the edge.
/// shift color with each rendering time
/// @param iter
/// @param max_iter
/// @return
int	color_palette(int iter, int max_iter, double time_s)
{
	int		r;
	int		g;
	int		b;
	double	phase;
	double	angle;

	phase = fmod(time_s * 0.05, 1.0);
	angle = TAU * (0.8 * ((double)iter / (double)max_iter) + phase);
	r = (int)(127.5 * (sin(angle) + 1.0));
	g = (int)(127.5 * (sin(angle + TAU / 2.0) + 1.0));
	b = (int)(127.5 * (sin(angle + 2.0 * TAU / 4.0) + 1.0));
	return (((r << 16) | (g << 8) | b));
}

void	pixel_color_data_fillin(int iter, int max_iter, int *color)
{
	double	time_s;

	time_s = mlx_get_time();
	if (iter == max_iter)
		*color = 0x000000;
	else
		*color = color_palette(iter, max_iter, time_s);
}

void	rendering_loop(t_context *ctx)
{
	int			x;
	int			y;
	t_complex	ptoc;
	int			iter;
	int			color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_to_complex(ctx, x, y, &ptoc);
			fractals_iter_dispatcher(ctx, ptoc, &iter);
			pixel_color_data_fillin(iter, ctx->max_iter, &color);
			mlx_put_pixel(ctx->img, x, y, color);
			x++;
		}
		y++;
	}
}
