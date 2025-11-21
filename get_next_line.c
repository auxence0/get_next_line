/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauvage <asauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:04:19 by asauvage          #+#    #+#             */
/*   Updated: 2025/11/21 16:53:33 by asauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*clear(char *str)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\n')
		i++;
	res = malloc(ft_strlen(str) - i);
	if (res == NULL)
		return (0);
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	return (res);
}

char	*result_line(char *str)
{
	int		i;
	char	*res;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (res == NULL)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

char	*ft_strcat(char *dst, char *src)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	len = ft_strlen(dst) + ft_strlen(src) + 1;
	res = malloc(sizeof(char) * len);
	if ((res == NULL) || (dst == NULL && src == NULL))
		return (0);
	while (dst != NULL && dst[j])
		res[i++] = dst[j++];
	j = 0;
	while (src != NULL && src[j])
		res[i++] = src[j++];
	res[i] = '\0';
	free(dst);
	return (res);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*result;
	int			n_bytes;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
		return (0);
	n_bytes = 1;
	while (n_bytes > 0 && ft_strchr(buffer, '\n') != 1)
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes == -1)
			return (0);
		buffer[n_bytes] = '\0';
		stash = ft_strcat(stash, buffer);
		if (stash[i++] == '\0')
			return (0);
	}
	result = result_line(stash);
	stash = clear(stash);
	return (result);
}

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
}