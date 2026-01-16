#ifndef FRACTO_HEADER_H
# define FRACTO_HEADER_H

# include <stdlib.h>
# define WIDTH 500
# define HEIGHT 500

// big context
typedef struct s_context
{
	void		*mlx;
	t_img		img;
	t_view		view;
	int			max_iter;
}				t_context;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr_pix;
	int		bpp_bits;
	int		line_len_bytes;
	int		endian;
}	t_img;

// a mathly informed practical bound for the chosen fractal
typedef struct s_view
{
	double	re_min;
	double	re_max;
	double	im_min;
	double	im_max;
}				t_view;

// coordinates
typedef struct s_complex
{
	double		re;
	double		im;
}				t_complex;

// meaningfully init struct
void			init_context(t_context *ctx);

// math part
void			mandelbrot_iter_math(t_complex c, int max_iter, int *out_iter);
int				escape_check(t_complex z);

// paint according to args
void			put_color_per_pixel(t_img *img, int x, int y, int color);
#endif // FRACTO_HEADER_H