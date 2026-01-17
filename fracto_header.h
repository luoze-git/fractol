#ifndef FRACTO_HEADER_H
# define FRACTO_HEADER_H

# include "libft/libft.h"
# include "mlx42/include/MLX42/MLX42.h"
# include <stdlib.h>
# define WIDTH 2000
# define HEIGHT 1400

// a mathly informed practical bound for the chosen fractal
typedef struct s_view
{
	double			re_min;
	double			re_max;
	double			im_min;
	double			im_max;
}					t_view;

typedef enum e_fractal_type
{
	FRACTAL_MANDELBROT,
	FRACTAL_JULIA,
	FRACTAL_TRICORN
}					t_fractal_type;

// coordinates
typedef struct s_complex
{
	double			r;
	double			i;
}					t_complex;

typedef struct s_context
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_view			view;
	int				max_iter;
	t_complex		const_arg;
	t_fractal_type	fractal_type;
}					t_context;

// meaningfully init struct
void				init_context(t_context *ctx);
void				set_view(t_context *ctx);
void				parse_args(int argc, char **argv, t_context *ctx);

// math part
void				julia_iter_math(t_complex z0, t_complex c, int max_iter,
						int *out_iter);
void				mandelbrot_iter_math(t_complex c, int max_iter,
						int *out_iter);
void	tricorn_iter_math(t_complex c, int max_iter, int *out_iter);
int					escape_check(t_complex z);
void				pixel_to_complex(t_context *ctx, int x, int y,
						t_complex *c);
void				zoom_view(t_view *v, double cx, double cy, double factor);

// paint according to args
void				bw_color(int iter, int max_iter, int *color);
void				iterate_all_pixels(t_context *ctx);

void				handle_key_callback(mlx_key_data_t key, void *param);
void				handle_scroll_callback(double xdelta, double ydelta,
						void *param);
#endif // FRACTO_HEADER_H
