/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:30:28 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/20 15:28:09 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	get_tex_pixel_color(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

void zero_texture_structs(t_game *game)
{
    ft_memset(&game->north, 0, sizeof(t_texture));
    ft_memset(&game->south, 0, sizeof(t_texture));
    ft_memset(&game->east, 0, sizeof(t_texture));
    ft_memset(&game->west, 0, sizeof(t_texture));
    ft_memset(&game->gun_idle, 0, sizeof(t_texture));
    ft_memset(&game->gun_fire, 0, sizeof(t_texture));
}

void	init_wall_textures(t_game *game)
{
	game->north.img = mlx_xpm_file_to_image(game->mlx, game->data->path_no,
			&game->north.width, &game->north.height);
	if (!game->north.img)
		print_error_and_exit("Failed to load north texture", game);
	game->north.addr = mlx_get_data_addr(game->north.img, &game->north.bpp,
			&game->north.line_len, &game->north.endian);
	game->south.img = mlx_xpm_file_to_image(game->mlx, game->data->path_so,
			&game->south.width, &game->south.height);
	if (!game->south.img)
		print_error_and_exit("Failed to load south texture", game);
	game->south.addr = mlx_get_data_addr(game->south.img, &game->south.bpp,
			&game->south.line_len, &game->south.endian);
	game->west.img = mlx_xpm_file_to_image(game->mlx, game->data->path_we,
			&game->west.width, &game->west.height);
	if (!game->west.img)
		print_error_and_exit("Failed to load west texture", game);
	game->west.addr = mlx_get_data_addr(game->west.img, &game->west.bpp,
			&game->west.line_len, &game->west.endian);
	game->east.img = mlx_xpm_file_to_image(game->mlx, game->data->path_ea,
			&game->east.width, &game->east.height);
	if (!game->east.img)
		print_error_and_exit("Failed to load east texture", game);
	game->east.addr = mlx_get_data_addr(game->east.img, &game->east.bpp,
			&game->east.line_len, &game->east.endian);
}

void	init_gun_textures(t_game *game)
{
	game->gun_idle.img = mlx_xpm_file_to_image(game->mlx,
			"textures/gun_idle.xpm",
			&game->gun_idle.width, &game->gun_idle.height);
	if (!game->gun_idle.img)
		print_error_and_exit("Failed to load gun_idle.xpm", game);
	game->gun_idle.addr = mlx_get_data_addr(game->gun_idle.img,
			&game->gun_idle.bpp, &game->gun_idle.line_len,
			&game->gun_idle.endian);
	game->gun_fire.img = mlx_xpm_file_to_image(game->mlx,
			"textures/gun_fire.xpm",
			&game->gun_fire.width, &game->gun_fire.height);
	if (!game->gun_fire.img)
		print_error_and_exit("Failed to load gun_fire.xpm", game);
	game->gun_fire.addr = mlx_get_data_addr(game->gun_fire.img,
			&game->gun_fire.bpp, &game->gun_fire.line_len,
			&game->gun_fire.endian);
}

void	init_textures(t_game *game)
{
	if (!game)
		return ;
	zero_texture_structs(game);
	init_wall_textures(game);
	init_gun_textures(game);
}

void	destroy_textures(t_game *game)
{
	if (game->north.img)
		mlx_destroy_image(game->mlx, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx, game->south.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx, game->east.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx, game->west.img);
	if (game->gun_idle.img)
		mlx_destroy_image(game->mlx, game->gun_idle.img);
	if (game->gun_fire.img)
		mlx_destroy_image(game->mlx, game->gun_fire.img);
}
