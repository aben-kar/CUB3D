/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_gc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:29:02 by zaakrab           #+#    #+#             */
/*   Updated: 2025/10/16 12:31:25 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_separator_gc(char c, char *separators)
{
	int	i;

	i = 0;
	while (separators[i])
	{
		if (c == separators[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_word_gc(char const *s1, char *sp)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	check = 1;
	while (s1[i] != '\0')
	{
		if (!is_separator_gc(s1[i], sp) && check == 1)
		{
			count += 1;
			check = 0;
		}
		else if (is_separator_gc(s1[i], sp))
			check = 1;
		i++;
	}
	return (count);
}

char	*ft_strsdup_gc(char const *s, size_t *j, char *sp, t_game *game)
{
	char	*result;
	size_t	i;
	size_t	k;

	i = *j;
	while (!is_separator_gc(s[*j], sp) && s[*j])
		(*j)++;
	result = gc_alloc((*j - i + 1) * sizeof(char), game);
	if (!result)
		return (NULL);
	k = 0;
	while (k < *j - i)
	{
		result[k] = s[i + k];
		k++;
	}
	result[k] = '\0';
	return (result);
}

char	**ft_split_gc(char const *s, char *c, t_game *game)
{
	size_t	i[2];
	char	**prr;
	size_t	len_word;

	i[0] = 0;
	i[1] = -1;
	len_word = count_word_gc(s, c);
	if (!s || !len_word)
		return (NULL);
	prr = gc_alloc((len_word + 1) * sizeof(char *), game);
	if (prr == NULL)
		return (NULL);
	while (++i[1] < len_word)
	{
		while (is_separator_gc(s[i[0]], c) && s[i[0]])
			i[0]++;
		if (s[i[0]])
		{
			prr[i[1]] = ft_strsdup_gc(s, &i[0], c, game);
			if (!prr[i[1]])
				return (NULL);
		}
	}
	prr[len_word] = NULL;
	return (prr);
}
