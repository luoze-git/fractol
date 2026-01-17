#include "fracto_header.h"

int	main(int argc, char **argv)
{
	t_context ctx;

	parse_args(argc, argv, &ctx);
	init_context(&ctx);
	iterate_all_pixels(&ctx);
	mlx_loop(ctx.mlx);
	mlx_terminate(ctx.mlx);
	return (EXIT_SUCCESS);
}