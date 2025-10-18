/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:48:20 by zaakrab           #+#    #+#             */
/*   Updated: 2025/10/16 12:29:22 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "../cub3D.h"

typedef struct s_game	t_game;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

void	*gc_alloc(size_t size, t_game *game);
void	gc_free_all(t_game *game);

// Prototypes
void	*ft_calloc_gc(size_t nelem, size_t size, t_game *game);
char	**ft_split_gc(char const *s, char *c, t_game *game);
char	*ft_strdup_gc(const char *s1, t_game *game);
char	*ft_strjoin_char_gc(const char *s, char c, t_game *game);
char	*ft_strjoin_gc(const char *s1, const char *s2, t_game *game);
char	*my_strjoin(char *s1, char *s2, t_game *game);
char	*ft_strndup(const char *s, size_t n, t_game *game);
char	*ft_strtrim_gc(char const *s1, char const *set, t_game *game);
char	*ft_substr_gc(const char *s, unsigned int start,
			size_t len, t_game *game);

#endif
