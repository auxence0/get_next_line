/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:04:53 by asauvage          #+#    #+#             */
/*   Updated: 2025/11/21 17:55:24 by asauvage         ###   ########.fr       */
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
	
	typedef struct s_line
	{
		char			*content;
		struct s_line	*next;
		struct s_line	*previous;
	}					t_line;
/* 
	int		ft_strlen(char *str);
	char	*clear(char *str);
	char	*result_line(char *str);
	char	*ft_strcat(char *dst, char *src);
	int		ft_strchr(char *str, char c);
	char	*get_next_line(int fd);
	 */
#endif