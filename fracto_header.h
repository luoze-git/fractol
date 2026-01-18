#ifndef FRACTO_HEADER_H
# define FRACTO_HEADER_H

/* Dependencies */
# include "libft.h"
# include "MLX42.h"
# include <stdlib.h>

/* Compile-time configuration */
# define WIDTH 2000  // window width
# define HEIGHT 1400 // window height
# define M_PI 3.14159265358979323846
# define TAU (2.0 * M_PI)

/* Core types */
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
	int				needs_rendering;
}					t_context;

/* Init / configuration */
void				init_context(t_context *ctx);
void				parse_args(int argc, char **argv, t_context *ctx);

/* Math / fractal iteration */
void				julia_iter_math(t_complex z0, t_complex c, int max_iter,
						int *out_iter);
void				mandelbrot_iter_math(t_complex c, int max_iter,
						int *out_iter);
void				tricorn_iter_math(t_complex c, int max_iter, int *out_iter);
void				pixel_to_complex(t_context *ctx, int x, int y,
						t_complex *c);
void				loop_callback(void *param);

/* Rendering */
void				pixel_color_data_fillin(int iter, int max_iter, int *color);
void				rendering_loop(t_context *ctx);
void				fractals_iter_dispatcher(t_context *ctx, t_complex c,
						int *iter);

/* Input callbacks */
void				handle_key_callback(mlx_key_data_t key, void *param);
void				handle_scroll_callback(double xdelta, double ydelta,
						void *param);
#endif // FRACTO_HEADER_H
