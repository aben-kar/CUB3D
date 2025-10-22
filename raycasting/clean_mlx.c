/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:57:00 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/20 14:08:02 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	cleanup_and_exit(t_game *game, int exit_code)
{
	if (!game)
		exit(exit_code);
	if (game->img)  // ← ADD THIS
        mlx_destroy_image(game->mlx, game->img);
	destroy_textures(game);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	gc_free_all(game);
	exit(exit_code);
}

int	close_window(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
}
