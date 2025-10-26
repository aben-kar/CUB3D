/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 07:43:54 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/10/25 22:06:23 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_read(int fd, char *nbuffer);

int		ft_strcherr(char *str, char sep);
int		ft_strlenr(char *str);
void	ft_strcatr(char *s1, char *s2, char **dest);
char	*ft_strdupr(char *s);
char	*ft_strjoinr(char *s1, char *s2);
void	*ft_callocr(size_t nmemb, size_t size);
char	*get_line(char *buffer);

#endif
