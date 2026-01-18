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
