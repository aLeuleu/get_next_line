/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:02:39 by alevra            #+#    #+#             */
/*   Updated: 2022/11/21 17:26:31 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	contains_endl_or_eof(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] < 0)
			return (-1);
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	read_buffer(char *buffer, int fd)
{
	int	byte_read;

	byte_read = read(fd, buffer, BUFFER_SIZE);
	ft_memset(buffer + byte_read, -1, (BUFFER_SIZE - byte_read));
}

void	append_line(char **line, char *buffer, int size_to_cat, int *len_line)
{
	int	size_to_realloc;

	if (size_to_cat > *len_line)
	{
		if (*len_line == 0)
			size_to_realloc = size_to_cat;
		else
			size_to_realloc = size_to_cat * 2;
		(*line) = ft_realloc((*line), size_to_realloc);
		*len_line = size_to_realloc;
	}
	ft_strlcat((*line), buffer, size_to_cat);
}

char	*get_next_line(int fd)
{
	char		*line;
	size_t		i;
	static char	buf[BUFFER_SIZE];
	int			len_nl_or_eof;
	int			len_line;

	line = NULL;
	i = 1;
	len_line = 0;
	if (buf[0] < 0 || BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	while (!contains_endl_or_eof(buf))
	{
		append_line(&line, buf, (BUFFER_SIZE * i++) + 1, &len_line);
		read_buffer(buf, fd);
	}
	if (line && *line == 0 && buf[0] == -1)
		return (free(line), NULL);
	len_line = strlen_untill(line, 0);
	len_nl_or_eof = strlen_untill(&buf[0], '\n') + 1;
	append_line(&line, buf, len_line + len_nl_or_eof + 1, &len_line);
	ft_memcpy(buf, buf + len_nl_or_eof, BUFFER_SIZE - len_nl_or_eof + 1);
	return (line);
}
