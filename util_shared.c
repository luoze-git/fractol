/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_shared.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:11:25 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/18 14:11:31 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fracto_header.h"

// start + fraction * range
void	pixel_to_complex(t_context *ctx, int x, int y, t_complex *out)
{
	double	fx;
	double	fy;

	fx = (double)x / WIDTH;
	fy = (double)y / HEIGHT;
	out->r = ctx->view.re_min + fx * (ctx->view.re_max - ctx->view.re_min);
	out->i = ctx->view.im_max - fy * (ctx->view.im_max - ctx->view.im_min);
}
