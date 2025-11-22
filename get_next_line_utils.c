/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:05:00 by asauvage          #+#    #+#             */
/*   Updated: 2025/11/22 18:43:25 by asauvage         ###   ########.fr       */
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

int	find_n(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strcat(char *src)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(src) + 1;
	res = malloc(sizeof(char) * len);
	if (res == NULL || src == NULL)
		return (0);
	while (src[i] != '\0')
	{
		res[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

t_line	*add_node(t_line *pre_node, char *buff)
{
	t_line	*new_node;

	new_node = malloc(sizeof(t_line));
	if (!new_node)
		return (0);
	if (!pre_node)
		new_node->previous = NULL;
	else
		new_node->previous = pre_node;
	new_node->content = ft_strcat(buff);
	new_node->next = NULL;
	return (new_node);
}

t_line	*first_node(t_line *node)
{
	while (node->previous != NULL)
		node = node->previous;
	return (node);
}

int	len_result(t_line *node)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	node = first_node(node);
	while (node != NULL && node->content != NULL)
	{
		while (node->content[i] && node->content[i] != '\n')
		{
			i++;
			len++;
		}
		i = 0;
		node = node->next;
	}
	return (len);
}

char	*result_line(t_line *node)
{
	int		i_r;
	int		i_n;
	int		len;
	char	*res;

	len = len_result(node);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (0);
	node = first_node(node);
	i_n = 0;
	i_r = 0;
	while (node != NULL && node->content != NULL)
	{
		while (node->content[i_n] && node->content[i_n] != '\n')
		{
			res[i_r] = node->content[i_n];
			i_r++;
			i_n++;
		}
		i_n = 0;
		node = node->next;
	}
	res[i_r] = '\0';
	return (res);
}

char	*next_line(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] != '\n')
		i++;
	res = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!res)
		return (0);
	i++;
	while (str[i])
	{
		res[j] = str[i];
		j++;
		i++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}

void	clear_node(t_line *node)
{
	int		i;
	t_line	*tmp_node;

	i = 0;
	node = first_node(node);
	while (find_n(node->content) == 0)
	{
		tmp_node = node;
		free(tmp_node->content);
		free(tmp_node);
		node = node->next;
	}
	node->content = next_line(node->content);
}

char	*get_next_line(int fd)
{
	static t_line	*node;
	t_line			*tmp_node;
	char			*result;
	char			*buff;
	int				bytes;

	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buff)
		return (0);
	bytes = 1;
	if (node)
		node = add_node(node, buff);
	while (bytes > 0 && find_n(buff) == 1 && find_n(node->content) == 1)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		tmp_node = add_node(node, buff);
		node->next = tmp_node;
		node = tmp_node;
	}
	result = result_line(node);
	clear_node(node);
	return (result);
}

int	main(void)
{
	char	*print;
	int		fd;
	int		i;

	fd = open("test.txt", O_RDONLY);
	i = 0;
	while (i < 2)
	{
		print = get_next_line(fd);
		printf("%s", print);
		free(print);
		i++;
	}
}
