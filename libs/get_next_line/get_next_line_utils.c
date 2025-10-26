/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:20:23 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/10/25 22:06:58 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strcherr(char *str, char sep)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == sep)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_strlenr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	ft_strcatr(char *s1, char *s2, char **dest)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		(*dest)[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		(*dest)[i] = s2[j];
		j++;
		i++;
	}
	(*dest)[i] = '\0';
}

char	*ft_strdupr(char *s)
{
	int		i;
	char	*p;

	if (!s)
		return (NULL);
	p = (char *)malloc((ft_strlenr(s) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoinr(char *s1, char *s2)
{
	char	*data;
	int		s1_lenght;
	int		s2_lenght;

	if (!s1)
		s1 = ft_callocr(1, 1);
	if (!s2)
		s2 = ft_callocr(1, 1);
	s1_lenght = ft_strlenr(s1);
	s2_lenght = ft_strlenr(s2);
	data = ft_callocr((s1_lenght + s2_lenght + 1), sizeof(char));
	if (!data)
		return (NULL);
	ft_strcatr(s1, s2, &data);
	free(s1);
	return (data);
}
