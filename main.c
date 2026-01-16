#include "fracto_header.h"

int	main(void)
{
	t_context ctx;

	init_context(&ctx);
	iterate_all_pixels(&ctx);
	mlx_loop(ctx.mlx);
    mlx_terminate(ctx.mlx);
	return (EXIT_SUCCESS);
}