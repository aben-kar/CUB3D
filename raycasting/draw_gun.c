/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:52:59 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/20 14:10:56 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	mouse_press(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		game->shooting = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		game->shooting = 0;
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x = -1;
	int			delta_x;
	double		rot_amount;

	(void)y;
	if (last_x == -1)
		last_x = x;
	delta_x = x - last_x;
	last_x = x;
	rot_amount = delta_x * 0.002;
	game->player->angle += rot_amount;
	game->player->dir_x = cos(game->player->angle);
	game->player->dir_y = sin(game->player->angle);
	game->player->plane_x = -game->player->dir_y * FOV;
	game->player->plane_y = game->player->dir_x * FOV;
	mlx_mouse_move(game->mlx, game->mlx_win,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	last_x = SCREEN_WIDTH / 2;
	return (0);
}

void	draw_gun(t_game *game)
{
	t_texture	*gun;
	t_data_gun	vr;

	if (game->shooting)
		gun = &game->gun_fire;
	else
		gun = &game->gun_idle;
	if (!gun || !gun->img || !gun->addr)
		return ;
	vr.start_x = (SCREEN_WIDTH / 2) - (gun->width / 2);
	vr.start_y = SCREEN_HEIGHT - gun->height;
	vr.gy = 0;
	while (vr.gy < gun->height)
	{
		vr.gx = 0;
		while (vr.gx < gun->width)
		{
			vr.color = get_tex_pixel_color(gun, vr.gx, vr.gy);
			if ((vr.color & 0x00FFFFFF) != 0x000000)
				my_mlx_pixel_put(game,
					vr.start_x + vr.gx, vr.start_y + vr.gy, vr.color);
			vr.gx++;
		}
		vr.gy++;
	}
}
