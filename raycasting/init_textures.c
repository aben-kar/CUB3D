#include "../cub3d.h"

void	init_textures(t_game *game)
{
	game->north.img = mlx_xpm_file_to_image(game->mlx, game->data->path_no,
		&game->north.width, &game->north.height);
	if (!game->north.img)
		print_error_and_exit("Failed to load north texture");
	game->north.addr = mlx_get_data_addr(game->north.img, &game->north.bpp,
		&game->north.line_len, &game->north.endian);


	game->south.img = mlx_xpm_file_to_image(game->mlx, game->data->path_so,
		&game->south.width, &game->south.height);
	if (!game->south.img)
		print_error_and_exit("Failed to load south texture");
	game->south.addr = mlx_get_data_addr(game->south.img, &game->south.bpp,
		&game->south.line_len, &game->south.endian);


	game->west.img = mlx_xpm_file_to_image(game->mlx, game->data->path_we,
		&game->west.width, &game->west.height);
	if (!game->west.img)
		print_error_and_exit("Failed to load west texture");
	game->west.addr = mlx_get_data_addr(game->west.img, &game->west.bpp,
		&game->west.line_len, &game->west.endian);


	game->east.img = mlx_xpm_file_to_image(game->mlx, game->data->path_ea,
		&game->east.width, &game->east.height);
	if (!game->east.img)
		print_error_and_exit("Failed to load east texture");
	game->east.addr = mlx_get_data_addr(game->east.img, &game->east.bpp,
		&game->east.line_len, &game->east.endian);


	// gun textures:
	game->gun_idle.img = mlx_xpm_file_to_image(game->mlx, "textures/gun_idle.xpm",
        &game->gun_idle.width, &game->gun_idle.height);
	if (!game->gun_idle.img)
		print_error_and_exit("Failed to load gun_idle.xpm");
	game->gun_idle.addr = mlx_get_data_addr(game->gun_idle.img, &game->gun_idle.bpp,
			&game->gun_idle.line_len, &game->gun_idle.endian);


	game->gun_fire.img = mlx_xpm_file_to_image(game->mlx, "textures/gun_fire.xpm",
			&game->gun_fire.width, &game->gun_fire.height);
	if (!game->gun_fire.img)
		print_error_and_exit("Failed to load gun_fire.xpm");
	game->gun_fire.addr = mlx_get_data_addr(game->gun_fire.img, &game->gun_fire.bpp,
			&game->gun_fire.line_len, &game->gun_fire.endian);

}
