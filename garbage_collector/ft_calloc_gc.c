/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_gc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:29:57 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/30 17:29:58 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	*ft_calloc_gc(size_t nelem, size_t size, t_game *game)
{
	void	*arr;

	if (size != 0 && nelem > 18446744073709551615UL / size)
		return (NULL);
	arr = gc_alloc(nelem * size, game);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, (nelem * size));
	return (arr);
}
