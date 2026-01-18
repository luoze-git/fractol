#include "fracto_header.h"

static void	print_usage(void)
{
	ft_putstr_fd("Usage: ./fractol <fractal> [options]\n", 2);
	ft_putstr_fd("Available fractals:\n", 2);
	ft_putstr_fd("  mandelbrot\n", 2);
	ft_putstr_fd("  tricorn\n", 2);
	ft_putstr_fd("  julia <re> <im>\n", 2);
}

void	parse_args(int argc, char **argv, t_context *ctx)
{
	if (argc < 2)
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		ctx->fractal_type = FRACTAL_MANDELBROT;
	else if (ft_strncmp(argv[1], "julia", 6) == 0)
	{
		ctx->fractal_type = FRACTAL_JULIA;
		if (argc < 4 || ft_atod(argv[2], &(ctx->const_arg.r)) != 0
			|| ft_atod(argv[3], &(ctx->const_arg.i)) != 0)
		{
			print_usage();
			exit(EXIT_FAILURE);
		}
	}
	else if (ft_strncmp(argv[1], "tricorn", 8) == 0)
		ctx->fractal_type = FRACTAL_TRICORN;
	else
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
}
