/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:49:10 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/28 17:31:41 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	check_is_rgb_digit(char **rgb_values, t_game *game)
{
	int	i;
	int	j;

	if (!rgb_values || !*rgb_values)
		return ;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (rgb_values[i][j])
		{
			if (!ft_isdigit(rgb_values[i][j]))
			{
				free_split(rgb_values);
				print_error_and_exit("RGB values must contain only digits",
					game);
			}
			j++;
		}
		i++;
	}
}

static void	check_virgule_count(char *line, t_game *game)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count > 2)
		print_error_and_exit("Invalid color format", game);
}

static char	**split_rgb_values(char *line, t_game *game)
{
	char	*cleand;
	char	**rgb_values;

	cleand = ft_strtrim(line, "\n");
	if (!cleand)
		print_error_and_exit("Memory allocation error", game);
	rgb_values = ft_split(cleand, ",");
	free(cleand);
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2]
		|| rgb_values[3] != NULL)
	{
		if (rgb_values)
			free_split(rgb_values);
		print_error_and_exit("Invalid color format", game);
	}
	return (rgb_values);
}

int	extract_rgb_color(char *line, t_game *game)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		color;

	if (!line || !line[0])
		return (0);
	check_virgule_count(line, game);
	rgb = split_rgb_values(line, game);
	check_is_rgb_digit(rgb, game);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_split(rgb);
		print_error_and_exit("Color values must be between 0 and 255", game);
	}
	color = (r << 16) | (g << 8) | b;
	free_split(rgb);
	return (color);
}
