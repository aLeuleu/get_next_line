/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:02:39 by alevra            #+#    #+#             */
/*   Updated: 2022/11/14 01:09:03 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)pointer;
	i = 0;
	while (i < count)
	{
		ptr[i] = value;
		i++;
	}
	return (pointer);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (nmemb > SIZE_MAX / size)
		return (NULL);
	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	return (ft_memset(res, 0, nmemb * size));
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static size_t	max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!dst)
		return (max((size_t)ft_strlen(src), size));
	if (!src && dst)
		return (size);
	while (dst[j] && j < size)
		j++;
	while (src[i] && ((j + i + 1) < size))
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j != size)
		dst[j + i] = '\0';
	return (j + ft_strlen((char *)src));
}

static int	contains_endl(char *str)
{
	size_t	i;

	i = -1;
	while(str && str[++i])
		if (str[i] == '\n' || str[i] < 0)
			return (1);
	return (0);
}

static char	*read_buffer(int fd, size_t buffer_size)
{
	char	*buff;

	buff = (char *)malloc(sizeof(char) * (buffer_size + 1) );
	read(fd, buff, buffer_size);
	buff[buffer_size + 1] = '\0';
	return (buff);
}

char	*realloc_by_buffer(char *oldstr, size_t newstr_size)
{
	char	*newstr;

	newstr = (char *)ft_calloc(newstr_size ,sizeof(char));
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

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>

int		strlen_untill(char *str, char delimiter)
{
	size_t len;

	len = 0;
	while (str && str[len] > 0 && str[len] != delimiter )
		len++;
	return (len);
}

char	*get_next_line(int fd)
{
	size_t	buffer_size;
	char	*buffer;
	char	*next_line;
	size_t	i;

	i = 1;
	buffer_size = 10;
	buffer = NULL;
    next_line = NULL;
 	while (!contains_endl(buffer))
	{
		next_line = realloc_by_buffer(next_line, buffer_size * i);
		ft_strlcat(next_line,buffer,buffer_size * i);		
		buffer = read_buffer(fd, buffer_size);
		i++;
	}
 	next_line = realloc_by_buffer(next_line, (buffer_size * (i - 2)) + strlen_untill(buffer, '\n') + 1);
	ft_strlcat(next_line, buffer, (buffer_size * (i - 2)) + strlen_untill(buffer, '\n') + 1);
    free(buffer);
	return (next_line);
}

int	main(int argc, char const *argv[])
{
	int fd;
	fd = open("./mon_fichier.txt", O_RDONLY);
	printf("1 : %s\n", get_next_line(fd));
	printf("2 : %s\n", get_next_line(fd));
	printf("3 : %s\n", get_next_line(fd));
    printf("4 : %s\n", get_next_line(fd));
    printf("5 : %s\n", get_next_line(fd));
    printf("6 : %s\n", get_next_line(fd));
    
}
// todo gerer les cas ou le file est deja entierement read