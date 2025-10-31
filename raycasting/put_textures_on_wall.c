/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures_on_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:24:55 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/31 14:50:36 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_ceiling(t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < game->ray->draw_start)
	{
		my_mlx_pixel_put(game, x, y, game->data->ceiling_color);
		y++;
	}
}

void	draw_floor(t_game *game, int x)
{
	int	y;

	y = game->ray->draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(game, x, y, game->data->floor_color);
		y++;
	}
}

int	get_tex_x(t_game *game, t_texture *tex)
{
	int		tex_x;
	double	wall_x;

	if (game->ray->side == 0)
		wall_x = game->player->y
			+ game->ray->perp_wall_dist * game->ray->ray_dir_y;
	else
		wall_x = game->player->x
			+ game->ray->perp_wall_dist * game->ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (game->ray->side == 0 && game->ray->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (game->ray->side == 1 && game->ray->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

t_texture	*select_wall_texture(t_game *game)
{
	t_texture	*tex;

	if (game->ray->side == 0)
	{
		if (game->ray->ray_dir_x > 0)
			tex = &game->west;
		else
			tex = &game->east;
	}
	else
	{
		if (game->ray->ray_dir_y > 0)
			tex = &game->north;
		else
			tex = &game->south;
	}
	return (tex);
}

void	draw_wall_column(t_game *game, int x)
{
	t_texture_data	vr;
	t_texture		*tex;
	int				tex_x;
	int				tex_y;

	draw_ceiling(game, x);
	tex = select_wall_texture(game);
	tex_x = get_tex_x(game, tex);
	vr.step = 1.0 * tex->height / game->ray->line_height;
	vr.tex_pos = (game->ray->draw_start - SCREEN_HEIGHT / 2
			+ game->ray->line_height / 2) * vr.step;
	vr.y = game->ray->draw_start;
	while (vr.y <= game->ray->draw_end)
	{
		tex_y = (int)vr.tex_pos & (tex->height - 1);
		vr.tex_pos += vr.step;
		vr.color = get_tex_pixel_color(tex, tex_x, tex_y);
		my_mlx_pixel_put(game, x, vr.y, vr.color);
		vr.y++;
	}
	draw_floor(game, x);
}
