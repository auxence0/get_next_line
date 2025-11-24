/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:04:19 by asauvage          #+#    #+#             */
/*   Updated: 2025/11/24 17:15:41 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*result_line(char *stash)
{
	int		i;
	char	*res;

	if (!stash || stash[0] == '\0')
		return (0);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	res = malloc(sizeof(char) * (i + (stash[i] == '\n') + 1));
	if (!res)
		return (0);
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

char	*clean_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		i_res;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (0);
	}
	i++;
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (0);
	i_res = 0;
	while (stash[i])
		new_stash[i_res++] = stash[i++];
	new_stash[i_res] = '\0';
	free(stash);
	return (new_stash);
}

char	*ft_join(char *stash, char *buff)
{
	int		i;
	int		j;
	char	*res;

	if (!stash && !buff)
		return (0);
	res = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buff) + 1));
	i = 0;
	j = 0;
	while (stash && stash[i])
		res[j++] = stash[i++];
	i = 0;
	while (buff && buff[i])
		res[j++] = buff[i++];
	res[j] = '\0';
	free(stash);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	char		*res;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	bytes = 1;
	while (bytes > 0 && (!stash || find_n(stash) == 1))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			return (0);
		}
		buff[bytes] = '\0';
		stash = ft_join(stash, buff);
		if (!stash)
		{
			free(buff);
			return (0);
		}
	}
	free(buff);
	res = result_line(stash);
	stash = clean_stash(stash);
	return (res);
}
/*
int	main(void)
{
	char *res;
	int fd;

	fd = open("test.txt", O_RDONLY);
	while ((res = get_next_line(fd)) != NULL)
	{
		printf("%s", res);
		free(res);
	}
	close(fd);
} */