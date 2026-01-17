#include "fracto_header.h"




void	handle_key_callback(mlx_key_data_t key, void *param)
{
	t_context *ctx = param;

	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(ctx->mlx);
}
