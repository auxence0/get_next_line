/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:05:00 by asauvage          #+#    #+#             */
/*   Updated: 2025/11/21 18:24:21 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dst, char *src)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	if (!src)
		return (0);
	res = malloc(sizeof(char) * (ft_strlen(dst) + ft_strlen(src) + 1));
	if (!res)
		return (0);
	while (!dst && dst[i])
	{
		res[i] = dst[i];
		i++;
	}
	j = 0;
	while (!src && src[j])
		res[i++] = src[j++];
	if (dst)
		free(dst);
	return (res);
}

char	*get_next_line(int fd)
{
	static t_line	*node;
	char	*res;

	res = malloc(sizeof(char) * BUFFER_SIZE);
	read(fd, res, BUFFER_SIZE);
	printf("%s", res);
	node->content = ft_strcat(node->content, res);
	node->next = NULL;
	node->previous = NULL;
	return (node->content);
}

int	main(void)
{
	char	*print;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	print = get_next_line(fd);
	printf("%s", print);
}