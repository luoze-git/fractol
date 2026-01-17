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
		tmp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = tmp;
		iter++;
	}
	*out_iter = iter;
}
