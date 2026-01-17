#include "fracto_header.h"

// start + fraction * range
// todo: review the scaling logic
void pixel_to_complex_c(t_context *ctx, int x, int y, t_complex *c)
{
	double fx;
	double fy;

	fx = (double)x / WIDTH;
	fy = (double)y / HEIGHT;
	c->re = ctx->view.re_min + fx * (ctx->view.re_max - ctx->view.re_min);
	c->im = ctx->view.im_max - fy * (ctx->view.im_max - ctx->view.im_min);
}

/// @brief quadratic complex fractals escape check
/// @param z 
/// @return true if the point escapes, false otherwise
int escape_check(t_complex z)
{
	return (z.re * z.re + z.im * z.im > 4.0);
}

/// @brief Mandelbrot experiment: input: c,
///  initial state: z = 0
/// @param c
/// @param max_iter
/// @param out_iter
void mandelbrot_iter_math(t_complex c, int max_iter, int *out_iter)
{
	t_complex z;
	int iter;
	double re2;
	double im2;

	z.re = 0.0;
	z.im = 0.0;
	iter = 0;
	while (iter < max_iter)
	{
		re2 = z.re * z.re;
		im2 = z.im * z.im;
		if (escape_check(z))
			break;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = re2 - im2 + c.re;
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

void iterate_all_pixels(t_context *ctx)
{
	int x;
	int y;
	t_complex c;
	int iter;
	int color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_to_complex_c(ctx, x, y, &c);
			mandelbrot_iter_math(c, ctx->max_iter, &iter);
			bw_color(iter, ctx->max_iter, &color);
			mlx_put_pixel(ctx->img, x, y, color);
			x++;
		}
		y++;
	}
}
