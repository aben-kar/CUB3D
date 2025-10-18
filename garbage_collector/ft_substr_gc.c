/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_gc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:30:34 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/30 17:30:36 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_substr_gc(const char *s, unsigned int start,
	size_t len, t_game *game)
{
	char	*subs;
	size_t	i;
	size_t	slen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup_gc("", game));
	if (start + len > slen)
		len = slen - start;
	subs = gc_alloc(len + 1, game);
	if (!subs)
		return (NULL);
	i = 0;
	while (s[start] != 0 && i < len)
		subs[i++] = s[start++];
	subs[i] = 0;
	return (subs);
}
