/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:07:04 by zaakrab           #+#    #+#             */
/*   Updated: 2025/10/28 16:38:33 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen_gnl(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *line, char *buff)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!line)
	{
		line = (char *)malloc(sizeof(char));
		line[0] = 0;
	}
	if (!line || !buff)
		return (NULL);
	str = malloc(sizeof(char)
			* (ft_strlen_gnl(line) + ft_strlen_gnl(buff) + 1));
	if (str == NULL)
		return (NULL);
	j = 0;
	i = -1;
	if (line)
		while (line[++i] != 0)
			str[i] = line[i];
	while (buff[j] != 0)
		str[i++] = buff[j++];
	str[ft_strlen_gnl(line) + ft_strlen_gnl(buff)] = 0;
	free(line);
	return (str);
}
