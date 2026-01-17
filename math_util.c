#include "fracto_header.h"

void	zoom_view(t_view *v, double cx, double cy, double factor)
{
	double	width;
	double	height;

	width = (v->re_max - v->re_min) * factor;
	height = (v->im_max - v->im_min) * factor;
	v->re_min = cx - width / 2.0;
	v->re_max = cx + width / 2.0;
	v->im_min = cy - height / 2.0;
	v->im_max = cy + height / 2.0;
}
