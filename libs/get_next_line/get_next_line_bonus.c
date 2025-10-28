/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:06:27 by zaakrab           #+#    #+#             */
/*   Updated: 2025/10/28 20:17:24 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*jib_line_hh(int fd, char *line)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr_gnl(line, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, (size_t)BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = 0;
		line = ft_strjoin_gnl(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*li_morah(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * ((ft_strlen_gnl(line) - i) + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	return (str);
}

char	*jib_line_mgad_hh(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] != 0 && line[i] != '\n')
		i++;
	str = (char *)malloc((i) + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] != 0 && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*lines[1024];
	char		*next_line;
	int			i;

	if (fd < 0 || (size_t)BUFFER_SIZE <= 0 || fd >= 1024)
	{
		i = -1;
		while (++i < 1024)
		{
			if (lines[i] != NULL)
			{
				free(lines[i]);
				lines[i] = NULL;
			}
		}
		return (NULL);
	}
	lines[fd] = jib_line_hh(fd, lines[fd]);
	if (lines[fd] == NULL)
		return (NULL);
	next_line = jib_line_mgad_hh(lines[fd]);
	lines[fd] = li_morah(lines[fd]);
	return (next_line);
}
