#ifndef FRACTO_HEADER_H
#define FRACTO_HEADER_H

#include <stdlib.h>
#include "mlx42/include/MLX42/MLX42.h"
#define WIDTH 2000
#define HEIGHT 1400

// a mathly informed practical bound for the chosen fractal
typedef struct s_view
{
	double re_min;
	double re_max;
	double im_min;
	double im_max;
} t_view;

typedef struct s_context
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_view view;
	int max_iter;
} t_context;

// coordinates
typedef struct s_complex
{
	double re;
	double im;
} t_complex;

// meaningfully init struct
void init_context(t_context *ctx);
void set_view(t_context *ctx);

// math part
void mandelbrot_iter_math(t_complex c, int max_iter, int *out_iter);
int escape_check_mandelbrot(t_complex z);
void pixel_to_complex_c(t_context *ctx, int x, int y, t_complex *c);
void zoom_view(t_view *v, double cx, double cy, double factor);

// paint according to args
void bw_color(int iter, int max_iter, int *color);
void iterate_all_pixels(t_context *ctx);

void handle_key_callback(mlx_key_data_t key, void *param);
void handle_scroll_callback(double xdelta, double ydelta, void *param);
#endif // FRACTO_HEADER_H
