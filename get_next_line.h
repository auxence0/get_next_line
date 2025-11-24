/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:04:53 by asauvage          #+#    #+#             */
/*   Updated: 2025/11/24 17:08:18 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2

# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* 	typedef struct s_line
	{
		char			*content;
		struct s_line	*next;
		struct s_line	*previous;
	}					t_line; */

int		ft_strlen(char *str);
char	*clean_stash(char *stash);
char	*result_line(char *stash);
char	*ft_strcat(char *stash, char *buff);
int		find_n(char *str);
char	*get_next_line(int fd);

#endif