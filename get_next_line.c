/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:04:19 by asauvage          #+#    #+#             */
/*   Updated: 2025/11/20 18:24:54 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

t_line	*new_node(char *content)
{
	t_line	*new_node;

	new_node = malloc(sizeof(t_line));
	if (new_node == NULL)
		return (0);
	new_node->content = content;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

/* char	*line_to_print(t_line	*node)
{
	char	*res;
	int		size;
	int		i_node;
	int		i_res;

	size = 0;
	i_node = 0;
	while (node != NULL)
	{
		while (node->content[i_node] && node->content[i_node] != '\n')
		{
			i_node++;
			size++;
			if (node->next == NULL && node->content[i_node] == '\n')
				continue;
		}
		if (node->content[i_node] == '\n')
			break;
		i_node = 0;
		node = node->previous;
	}
	res = malloc(sizeof(char) * (size + 1));
	if (res == NULL)
		return (0);
	i_node = 0;
	i_res = 0;
	while (node != NULL)
	{
		while (node->content[i_node])
		{
			res[i_res++] = node->content[i_node++];
			if (node->content[i_node] == '\n')
			{
				res[i_res] = '\n';
				return (res);
			}
		}
		i_node = 0;
		node = node->next;
	}
	return (res);
} */

char	*line_to_print(t_line *node)
{
	char	*res;
	int		size;
	int		i;
	int		j;
	int		nb_nw_line;

	nb_nw_line = 0;
	size = 0;
	i = 0;
	node = node->previous;
	while (node != NULL && nb_nw_line != 2)
	{
		while (node->content[i])
		{
			if (node->content[i] == '\n')
				nb_nw_line++;
			i++;
			size++;
		}
		i = 0;
		node = node->previous;
	}
	j = 0;
	res = malloc(sizeof(char) * size);
	while (node->content[i] != '\n')
		i++;
	while (node->content[i] != '\n' && node != NULL)
		res[j++] = node->content[i++];
	return (res);
}
char	*get_next_line(int fd)
{
	char		*tmp;
	char		*res;
	int			b;
	t_line		*node;
	t_line		*tmp_node;

	tmp = malloc(sizeof(char) * BUFFER_SIZE);
	if (tmp == NULL)
		return (0);
	b = read(fd, tmp, BUFFER_SIZE);
	node = new_node(tmp);
	while (b == BUFFER_SIZE && verif(tmp))
	{
		b = read(fd, tmp, BUFFER_SIZE);
		if (b == -1)
			return (0);
		tmp_node = new_node(tmp);
		node->next = tmp_node;
		tmp_node->previous = node;
		node = node->next;
	}
	res = line_to_print(node);
	return (res);
}

int	main(void)
{
	char	*res;

	printf("%d", BUFFER_SIZE);
	res = get_next_line(open("test.txt", O_RDONLY));
	//printf("%s", res);
}