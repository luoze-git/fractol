#include "fracto_header.h"

/// @brief quadratic complex fractals escape check
/// @param z
/// @return true if the point escapes, false otherwise
static int	escape_check(t_complex z)
{
	return (z.r * z.r + z.i * z.i > 4.0);
}

/// Julia experiment: pixel as z0,
/// constant: c = fixed and given as cmd arg,
/// z0 is the current position, z = z^2 + c
void	julia_iter_math(t_complex z0, t_complex c, int max_iter, int *out_iter)
{
	t_complex	z;
	int			iter;
	double		tmp;

	z = z0;
	iter = 0;
	while (iter < max_iter)
	{
		if (escape_check(z))
			break ;
		tmp = z.r * z.r - z.i * z.i + c.r;
		z.i = 2.0 * z.r * z.i + c.i;
		z.r = tmp;
		iter++;
	}
	*out_iter = iter;
}
void	tricorn_iter_math(t_complex c, int max_iter, int *out_iter)
{
	t_complex	z;
	int			iter;
	double		r2;
	double		i2;

	z.r = 0.0;
	z.i = 0.0;
	iter = 0;
	while (iter < max_iter)
	{
		r2 = z.r * z.r;
		i2 = z.i * z.i;
		if (escape_check(z))
			break ;
		z.i = -2.0 * z.r * z.i + c.i;
		z.r = r2 - i2 + c.r;
		iter++;
	}
	*out_iter = iter;
}

/// @brief Mandelbrot experiment:
///  initial state: z = 0, constant c = pixel position,
/// @param c
/// @param max_iter
/// @param out_iter
void	mandelbrot_iter_math(t_complex c, int max_iter, int *out_iter)
{
	t_complex	z;
	int			iter;
	double		r2;
	double		i2;

	z.r = 0.0;
	z.i = 0.0;
	iter = 0;
	while (iter < max_iter)
	{
		r2 = z.r * z.r;
		i2 = z.i * z.i;
		if (escape_check(z))
			break ;
		z.i = 2.0 * z.r * z.i + c.i;
		z.r = r2 - i2 + c.r;
		iter++;
	}
	*out_iter = iter;
}

/// @brief choosing which fractal to compute
/// @param ctx
/// @param c
/// @param iter
void	fractals_iter_dispatcher(t_context *ctx, t_complex c, int *iter)
{
	if (ctx->fractal_type == FRACTAL_MANDELBROT)
		mandelbrot_iter_math(c, ctx->max_iter, iter);
	if (ctx->fractal_type == FRACTAL_JULIA)
		julia_iter_math(c, ctx->const_arg, ctx->max_iter, iter);
	if (ctx->fractal_type == FRACTAL_TRICORN)
		tricorn_iter_math(c, ctx->max_iter, iter);
}
