/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:44:25 by asauvage          #+#    #+#             */
/*   Updated: 2025/11/25 13:36:30 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2

# endif

# ifndef FD_MAX
#  define FD_MAX 4096
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(char *str);
char	*clean_stash(char *stash);
char	*result_line(char *stash);
char	*ft_join(char *stash, char *buff);
int		find_n(char *str);
char	*search_line(int fd, char *buff, char *stash, ssize_t bytes);
char	*get_next_line(int fd);
int		start_index(char *stash, int i);

#endif