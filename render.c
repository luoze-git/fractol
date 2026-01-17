#include "fracto_header.h"

// start + fraction * range
// todo: review the scaling logic
void pixel_to_complex(t_context *ctx, int x, int y, t_complex *out)
{
	double fx;
	double fy;

	fx = (double)x / WIDTH;
	fy = (double)y / HEIGHT;
	out->r = ctx->view.re_min + fx * (ctx->view.re_max - ctx->view.re_min);
	out->i = ctx->view.im_max - fy * (ctx->view.im_max - ctx->view.im_min);
}

/// @brief quadratic complex fractals escape check
/// @param z
/// @return true if the point escapes, false otherwise
int escape_check(t_complex z)
{
	return (z.r * z.r + z.i * z.i > 4.0);
}

/// @brief Mandelbrot experiment:
///  initial state: z = 0, constant c = pixel position,
/// @param c
/// @param max_iter
/// @param out_iter
void mandelbrot_iter_math(t_complex c, int max_iter, int *out_iter)
{
	t_complex z;
	int iter;
	double r2;
	double i2;

	z.r = 0.0;
	z.i = 0.0;
	iter = 0;
	while (iter < max_iter)
	{
		r2 = z.r * z.r;
		i2 = z.i * z.i;
		if (escape_check(z))
			break;
		z.i = 2.0 * z.r * z.i + c.i;
		z.r = r2 - i2 + c.r;
		iter++;
	}
	*out_iter = iter;
}

void bw_color(int iter, int max_iter, int *color)
{
	if (iter == max_iter)
		*color = 0x000000;
	else
		*color = 0xFFFFFF;
}

/// @brief choosing which fractal to compute
/// @param ctx
/// @param c
/// @param iter
void fractals_iter_dispatcher(t_context *ctx, t_complex c, int *iter)
{
	if (ctx->fractal_type == FRACTAL_MANDELBROT)
		mandelbrot_iter_math(c, ctx->max_iter, iter);
	if (ctx->fractal_type == FRACTAL_JULIA)
		julia_iter_math(c, ctx->const_arg, ctx->max_iter, iter);
	if (ctx->fractal_type == FRACTAL_TRICORN)
		tricorn_iter_math(c, ctx->max_iter, iter);
}

void iterate_all_pixels(t_context *ctx)
{
	int x;
	int y;
	t_complex ptoc;
	int iter;
	int color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_to_complex(ctx, x, y, &ptoc);
			fractals_iter_dispatcher(ctx, ptoc, &iter);
			bw_color(iter, ctx->max_iter, &color);
			mlx_put_pixel(ctx->img, x, y, color);
			x++;
		}
		y++;
	}
}
