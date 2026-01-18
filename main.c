/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:11:14 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/18 14:11:15 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fracto_header.h"

int	main(int argc, char **argv)
{
	t_context	ctx;

	ctx = (t_context){0};
	parse_args(argc, argv, &ctx);
	init_context(&ctx);
	rendering_loop(&ctx);
	mlx_loop(ctx.mlx);
	mlx_terminate(ctx.mlx);
	return (EXIT_SUCCESS);
}
