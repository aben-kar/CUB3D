/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_gc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:31:41 by zaakrab           #+#    #+#             */
/*   Updated: 2025/10/18 20:31:42 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	get_trim_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

static int	get_trim_end(char const *s1, char const *set)
{
	int	j;

	j = ft_strlen(s1) - 1;
	while (j >= 0 && ft_strchr(set, s1[j]))
		j--;
	return (j);
}

static char	*empty_trim(t_game *game)
{
	char	*dest;

	dest = gc_alloc(1, game);
	if (!dest)
		return (NULL);
	dest[0] = '\0';
	return (dest);
}

char	*ft_strtrim_gc(char const *s1, char const *set, t_game *game)
{
	int		i;
	int		j;
	char	*dest;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	i = get_trim_start(s1, set);
	if (i == (int)ft_strlen(s1))
		return (empty_trim(game));
	j = get_trim_end(s1, set);
	dest = gc_alloc((j - i + 2), game);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1 + i, j - i + 1);
	dest[j - i + 1] = '\0';
	return (dest);
}
