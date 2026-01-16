#ifndef FRACTO_HEADER_H
# define FRACTO_HEADER_H

#include <stdlib.h>
#define WIDTH 500
#define HEIGHT 500

// big context
typedef struct s_context
{
	void	*mlx;
	mlx_image_t	*img;
	t_view	view;
	int		max_iter;
}			t_context;

// a mathly informed practical bound for the chosen fractal
typedef struct s_view
{
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
}			t_view;

// coordinates
typedef struct s_complex
{
	double	re;
	double	im;
}			t_complex;

// meaningfully init struct
void		init_context(t_context *ctx);

// math part
void		mandelbrot_iter_math(t_complex c, int max_iter, int *out_iter);
int			escape_check(t_complex z);

// paint according to args
void		put_pixel(mlx_image_t *img, int x, int y, int color);
#endif // FRACTO_HEADER_H