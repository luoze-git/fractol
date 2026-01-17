#include "fracto_header.h"

// todo add saftey initiator
void	parse_args(int argc, char **argv, t_context *ctx)
{
	if (argc < 2)
		return ;
	// error_print_and_dealing();
	if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
	{
		ctx->fractal_type = FRACTAL_MANDELBROT;
	}
	if (ft_strncmp(argv[1], "julia", 5) == 0)
	{
		ctx->fractal_type = FRACTAL_JULIA;
		if (ft_atod(argv[2], &(ctx->const_arg.re)) != 0)
			return ;
		// error_print_and_dealing();
		if (ft_atod(argv[3], &(ctx->const_arg.im)) != 0)
			return ;
		// error_print_and_dealing();
	}
}