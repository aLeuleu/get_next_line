/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:02:39 by alevra            #+#    #+#             */
/*   Updated: 2022/11/16 18:19:59 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	contains_endl_or_eof(char *str)
{
	size_t	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\n')
			return (1);
		if (str[i] < 0)
			return (-1);
	}
	return (0);
}

char	*realloc_by_buffer(char *oldstr, size_t newstr_size)
{
	char	*newstr;

	if (!newstr_size)
		newstr = (char *)ft_calloc(1, sizeof(char));
	else
		newstr = (char *)ft_calloc(newstr_size, sizeof(char));
	if (!newstr)
	{
		if (oldstr)
			free(oldstr);
		return (NULL);
	}
	if (oldstr)
	{
		ft_strlcat(newstr, oldstr, newstr_size);
		free(oldstr);
	}
	return (newstr);
}

int	strlen_untill(char *str, char delimiter)
{
	size_t	len;

	len = 0;
	while (str && str[len] > 0 && str[len] != delimiter)
		len++;
	return (len);
}

void	append_next_line_and_read_buffer(char **next_line, char *buffer, int fd,
		int i)
{
	int	byte_read;

	(*next_line) = realloc_by_buffer((*next_line), (BUFFER_SIZE * i) + 1);
	ft_strlcat((*next_line), buffer, (BUFFER_SIZE * i) + 1);
	byte_read = read(fd, buffer, BUFFER_SIZE);
	ft_memset(buffer + byte_read, -1, (BUFFER_SIZE - byte_read));
}

char	*get_next_line(int fd)
{
	char		*next_line;
	size_t		i;
	static char	buffer[BUFFER_SIZE];
	int			len_untill_nl_or_eof;

	next_line = NULL;
	i = 1;
	if (buffer[0] < 0 || BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	while (!contains_endl_or_eof(buffer))
		append_next_line_and_read_buffer(&next_line, buffer, fd, i++);
	len_untill_nl_or_eof = strlen_untill(&buffer[0], '\n') + 1;
	next_line = realloc_by_buffer(next_line, ft_strlen(next_line)
			+ len_untill_nl_or_eof + 1);
	ft_strlcat(next_line, buffer, ft_strlen(next_line) + len_untill_nl_or_eof);
	ft_strlcat(next_line, "\n", ft_strlen(next_line) + len_untill_nl_or_eof + 1);
	ft_memcpy(buffer, buffer + len_untill_nl_or_eof, BUFFER_SIZE
		- len_untill_nl_or_eof);
	if (buffer[BUFFER_SIZE - 1] != -1)
		ft_memset(buffer + (BUFFER_SIZE - len_untill_nl_or_eof), 0,
			len_untill_nl_or_eof);
	return (next_line);
}
