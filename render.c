#include "fracto_header.h"

// start + fraction * range
// todo: review the scaling logic
void pixel_to_complex(t_context *ctx, int x, int y, t_complex *c)
{
    double fx;
    double fy;

    fx = (double)x / WIDTH;
    fy = (double)y / HEIGHT;

    c->re = ctx->view.re_min + fx * (ctx->view.re_max - ctx->view.re_min);
    c->im = ctx->view.im_max - fy * (ctx->view.im_max - ctx->view.im_min);
}

int escape_check_mandelbrot(t_complex z)
{
    return (z.re * z.re + z.im * z.im > 4.0);
}

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
        if (escape_check_mandelbrot(z))
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

void	put_color_data(t_img *img, int x, int y, int color)
{
	char	*dst;
	dst = img->addr_pix
		+ y * img->line_len_bytes
		+ x * (img->bpp_bits / 8);
	*(unsigned int *)dst = color;
}


void iterate_all_pixels(t_context *ctx)
{
    int x;
    int y;
    t_complex z;
    int iter;
    int color;

    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            pixel_to_complex(ctx, x, y, &z);
            mandelbrot_iter_math(z, ctx->max_iter, &iter);
            bw_color(iter, ctx->max_iter, &color);
            put_color_data(&ctx->img, x, y, color);
            x++;
        }
        y++;
    }
}
