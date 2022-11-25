/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:02:39 by alevra            #+#    #+#             */
/*   Updated: 2022/11/25 09:32:18 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	contains_endl_or_eof(char *str, int size)
{
	int	i;

	i = 0;
	while (str && i < size && str[i])
	{
		if (str[i] < 0)
			return (-1);
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int	read_buffer(char *buffer, int fd)
{
	int	byte_read;

	byte_read = read(fd, buffer, BUFFER_SIZE);
	if (byte_read < 0)
	{
		ft_memset_gnl(buffer, 0, BUFFER_SIZE);
		return (0);
	}
	else
		ft_memset_gnl(buffer + byte_read, -1, (BUFFER_SIZE - byte_read));
	return (1);
}

static void
	append_line(char **line, char *buffer, int size_to_cat, int *len_line)
{
	int	size_to_realloc;

	if (size_to_cat > *len_line)
	{
		if (*len_line == 0)
			size_to_realloc = size_to_cat;
		else
			size_to_realloc = size_to_cat * 2;
		(*line) = ft_realloc_gnl((*line), size_to_realloc);
		if (!*line)
			return ;
		*len_line = size_to_realloc;
	}
	ft_strlcat_gnl((*line), buffer, size_to_cat);
}

char	*get_next_line(int fd)
{
	char		*line;
	size_t		i;
	static char	buf[MAX_OPEN][BUFFER_SIZE +1];
	int			len_nl_eof;
	int			len_line;

	line = NULL;
	i = 1;
	len_line = 0;
	if (buf[fd][0] < 0 || BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	while (!contains_endl_or_eof(buf[fd], BUFFER_SIZE))
	{
		append_line(&line, buf[fd], (BUFFER_SIZE * i++), &len_line);
		if (!read_buffer(buf[fd], fd))
			return (free(line), NULL);
	}
	if (line && *line == 0 && buf[fd][0] == -1)
		return (free(line), NULL);
	len_line = strlen_until_gnl(line, 0);
	len_nl_eof = strlen_until_gnl(&buf[fd][0], '\n') + 1;
	append_line(&line, buf[fd], len_line + len_nl_eof + 1, &len_line);
	ft_memcpy_gnl(buf[fd], buf[fd] + len_nl_eof, BUFFER_SIZE - len_nl_eof + 1);
	return (line);
}
