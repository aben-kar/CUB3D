/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:30:29 by zaakrab           #+#    #+#             */
/*   Updated: 2025/10/16 12:31:41 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_strndup(const char *s, size_t n, t_gc **gc)
{
	size_t	i;
	size_t	j;
	char	*dup;

	i = 0;
	while (s[i] && i < n)
		i++;
	dup = gc_alloc((i + 1), gc);
	if (!dup)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dup[j] = s[j];
		j++;
	}
	dup[i] = '\0';
	return (dup);
}
