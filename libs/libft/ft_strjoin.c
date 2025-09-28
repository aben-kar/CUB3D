/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:22:26 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/28 16:05:22 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*concate;
// 	size_t	len_s1;
// 	size_t	len_s2;

// 	if (!s1)
// 		return ((char *)s2);
// 	if (!s2)
// 		return ((char *)s1);
// 	len_s1 = ft_strlen(s1);
// 	len_s2 = ft_strlen(s2);
// 	concate = (char *)ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
// 	if (concate == NULL)
// 		return (NULL);
// 	ft_memcpy(concate, s1, len_s1);
// 	ft_memcpy(concate + len_s1, s2, len_s2);
// 	return (concate);
// }


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, s1_len);
	ft_memcpy(result + s1_len, s2, s2_len);
	result[s1_len + s2_len] = '\0';
	return (result);
}