/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 09:46:08 by asauvage          #+#    #+#             */
/*   Updated: 2026/02/26 10:22:03 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	find_n(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin(char *stash, char *buff)
{
	int	i;

	i = ft_strlen(stash) + ft_strlen(buff) + 1;
	char	*res = malloc(i + 1);
	if (!res)
		return (NULL);
	i = 0;
	int	j = 0;
	while (stash && stash[i])
		res[j++] = stash[i++];
	i = 0;
	while (buff && buff[i])
		res[j++] = buff[i++];
	res[j] = '\0';
	if (stash)
		free(stash);
	return (res);
}

char	*next_line(char *stash)
{
	int	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	char	*res = malloc(ft_strlen(stash) - i + 1);
	if (!res)
		return (NULL);
	int	j = 0;
	i++;
	while (stash[i])
		res[j++] = stash[i++];
	res[j] = '\0';
	free(stash);
	return (res);
}

char	*result_line(char *stash)
{
	int	i;

	i = 0;
	if (!stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	char	*res = malloc(i + (stash[i] == '\n') + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		res[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

char	*search_line(int fd, char *stash, char *buff, ssize_t bytes)
{
	while (bytes > 0 && find_n(stash))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			if (stash)
				free(stash);
			return (NULL);
		}
		buff[bytes] = '\0';
		stash = ft_strjoin(stash, buff);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static	char	*stash;
	char			*buff;
	char			*line;
	ssize_t			bytes;

	if (fd < 0 || BUFFER_SIZE < 1)
	{
		if (stash)
			free(stash);
		return (0);
	}
	bytes = 1;
	buff = malloc(BUFFER_SIZE + 1);
	stash = search_line(fd, stash, buff, bytes);
	if (buff)
		free(buff);
	if (!stash)
		return (NULL);
	line = result_line(stash);
	if (!line)
	{
		if (stash)
			free(stash);
		return (NULL);
	}
	stash = next_line(stash);
	return (line);
}

int	main(int ac, char **av)
{
	char	*res;
	int		fd;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	int	i = 0;
	while ((res = get_next_line(fd)) && i < 2)
	{
		printf("%s", res);
		i++;
		free(res);
	}
	return (0);
}
