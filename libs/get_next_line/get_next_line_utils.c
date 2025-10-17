/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:36:02 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/08 17:50:07 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	*ft_calloc_gc(size_t count, size_t size, t_gc **gc)
{
	unsigned char	*s;
	size_t			i;

	i = 0;
	if (size != 0 && (count > SIZE_MAX / size))
		return (NULL);
	s = gc_alloc(count * size, gc);
	if (s == NULL)
		return (NULL);
	while (i < count * size)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

char	*ft_strjoin_get(char *s1, char *s2, t_gc **gc)
{
	char	*concate;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		s1 = ft_calloc_gc(1, sizeof(char), gc);
	if (!s2)
		s2 = ft_calloc_gc(1, sizeof(char), gc);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	concate = ft_calloc_gc((len_s1 + len_s2 + 1), sizeof(char), gc);
	if (concate == NULL)
		return (NULL);
	ft_memcpy(concate, s1, len_s1);
	ft_memcpy(concate + len_s1, s2, len_s2);
	// free(s1);
	return (concate);
}

char	*gnl_strdup_gc(const char *s1, t_gc **gc)
{
	size_t	len;
	char	*ptr;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	ptr = ft_calloc_gc((len + 1), sizeof(char), gc);
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
