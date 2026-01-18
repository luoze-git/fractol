#include "fracto_header.h"

// start + fraction * range
// todo: review the scaling logic
void	pixel_to_complex(t_context *ctx, int x, int y, t_complex *out)
{
	double	fx;
	double	fy;

	fx = (double)x / WIDTH;
	fy = (double)y / HEIGHT;
	out->r = ctx->view.re_min + fx * (ctx->view.re_max - ctx->view.re_min);
	out->i = ctx->view.im_max - fy * (ctx->view.im_max - ctx->view.im_min);
}
