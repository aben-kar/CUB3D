/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:28:12 by zaakrab           #+#    #+#             */
/*   Updated: 2025/10/16 12:31:57 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cub3D.h"

void	*gc_alloc(size_t size, t_game *game)
{
	void	*ptr;
	t_gc	*new_node;

	if (!game)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_gc));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	new_node->ptr = ptr;
	new_node->next = game->gc; // insert at head
	game->gc = new_node;
	return (ptr);
}

void	gc_free_all(t_game *game)
{
	t_gc	*tmp;

	if (!game)
		return;
	while (game->gc)
	{
		tmp = game->gc;
		game->gc = game->gc->next;
		free(tmp->ptr);
		free(tmp);
	}
}
