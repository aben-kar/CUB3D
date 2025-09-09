/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:39:37 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/08 17:48:42 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*s;
	size_t			i;

	i = 0;
	if (size != 0 && (count > SIZE_MAX / size))
		return (NULL);
	s = (unsigned char *)malloc(count * size);
	if (s == NULL)
		return (NULL);
	while (i < count * size)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

char	*ft_strjoin_get(char *s1, char *s2)
{
	char	*concate;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
		s2 = ft_calloc(1, sizeof(char));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	concate = (char *)ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
	if (concate == NULL)
		return (NULL);
	ft_memcpy(concate, s1, len_s1);
	ft_memcpy(concate + len_s1, s2, len_s2);
	free(s1);
	return (concate);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ptr;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	ptr = (char *)ft_calloc((len + 1), sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, len);
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
