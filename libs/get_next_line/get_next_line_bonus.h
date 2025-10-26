/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:06:36 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/30 17:40:20 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *line, char *buff);
char	*ft_strchr_gnl(char *s, int c);
size_t	ft_strlen_gnl(char *s);
char	*li_morah(char *line);
char	*jib_line_hh(int fd, char *line);
char	*jib_line_mgad_hh(char *line);

#endif
