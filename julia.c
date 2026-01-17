#include "fracto_header.h"

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
