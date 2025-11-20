/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:28:29 by asauvage          #+#    #+#             */
/*   Updated: 2025/11/20 18:48:28 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	nb_w(int fd)
{
	int		tot;
	int		b;
	char	*t;

	t = malloc(BUFFER_SIZE);
	tot = 0;
	b = read(fd, t, BUFFER_SIZE);
	while (b > 0)
	{
		b = read(fd, t, BUFFER_SIZE);
		tot = tot + BUFFER_SIZE; 
	}
	return (tot);
}

int	verif(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (i);
}

void	f_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i++] = src[j];
	}
	dest[i] = '\0';
}

char	*join(char **str, int size)
{
	int		i;
	char	*res;
	
	i = 0;
	res = malloc(sizeof(char) * (size * BUFFER_SIZE));
	while (str[i])
	{
		f_strcat(res, str[i++]);
	}
	return (res);
}

char	*line(int fd)
{
	char			*tmp;
	static int		i;
	int				b;
	char			**res;
	char			*result;

	i = 0;
	tmp = malloc(sizeof(char) * BUFFER_SIZE);
	res = malloc(sizeof(char *) * nb_w(fd));
	b = read(fd, tmp, BUFFER_SIZE);
	while (b > 0)
	{
		printf("test");	
		b = read(fd, tmp, BUFFER_SIZE);
		res[i] = tmp;
		i++;
	}
	result = join(res, i);
	return (result);
}

int	main(void)
{
	char	*res;

	res = line(open("test.txt", O_RDONLY));
}