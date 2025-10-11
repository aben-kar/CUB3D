#include "../cub3d.h"

void	init_textures(t_game *game)
{
	game->north.img = mlx_xpm_file_to_image(game->mlx, game->data->path_no,
		&game->north.width, &game->north.height);
	game->north.addr = mlx_get_data_addr(game->north.img, &game->north.bpp,
		&game->north.line_len, &game->north.endian);

	game->south.img = mlx_xpm_file_to_image(game->mlx, game->data->path_so,
		&game->south.width, &game->south.height);
	game->south.addr = mlx_get_data_addr(game->south.img, &game->south.bpp,
		&game->south.line_len, &game->south.endian);

	game->west.img = mlx_xpm_file_to_image(game->mlx, game->data->path_we,
		&game->west.width, &game->west.height);
	game->west.addr = mlx_get_data_addr(game->west.img, &game->west.bpp,
		&game->west.line_len, &game->west.endian);

	game->east.img = mlx_xpm_file_to_image(game->mlx, game->data->path_ea,
		&game->east.width, &game->east.height);
	game->east.addr = mlx_get_data_addr(game->east.img, &game->east.bpp,
		&game->east.line_len, &game->east.endian);
}
