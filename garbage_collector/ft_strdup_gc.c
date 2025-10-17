/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_gc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:29:08 by zaakrab           #+#    #+#             */
/*   Updated: 2025/10/16 12:31:29 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_strdup_gc(const char *s1, t_game *game)
{
	char	*dest;
	size_t	i;

	i = 0;
	while (s1[i] != 0)
		i++;
	dest = gc_alloc((i + 1), game);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
