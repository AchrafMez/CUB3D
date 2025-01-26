/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:24:44 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/26 04:40:34 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include "../lib_bonus/lib.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_read(int fd, char *sbuff, char *buffer);
char	*get_next_line(int fd);
int		ft_strlen(const char *s);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		contains_nl(char *sbuff);
char	*copy_until_nl(char *sbuff);
char	*copy_after_nl(char *in);

#endif