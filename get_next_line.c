/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:02:39 by alevra            #+#    #+#             */
/*   Updated: 2022/11/16 01:01:33 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}


static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destc;
	const unsigned char	*srcc;
	int					i;

	if (!dest || !src)
		return (NULL);
	srcc = (unsigned char *)src;
	destc = (unsigned char *)dest;
	i = 0;
	while (n--)
	{
		destc[i] = srcc[i];
		i++;
	}
	return (dest);
}

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned char	*ptr;
	size_t			i;

	if (count == 0)    //debug
		return (NULL); //debug
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

	if (!nmemb || !size) //debug
		return (NULL);   //debug
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	return (ft_memset(res, 0, nmemb * size));
}


static size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!dst)
		return (0);
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

static int	contains_endl_or_eof(char *str)
{
	size_t	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\n')
		{
			//printf("Le buffer contient endl !\n");
			return (1);
		}
		if (str[i] < 0)
		{
			//printf("Le buffer contient eof !\n");
			return (1);
		}
	}
	//printf("Le buffer ne contient pas endl ou eof \n");
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

#include <fcntl.h>
#include <stddef.h>

int	strlen_untill(char *str, char delimiter)
{
	size_t	len;

	len = 0;
	while (str && str[len] > 0 && str[len] != delimiter)
		len++;
	return (len);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	size_t		i;
	static char	buffer[BUFFER_SIZE];
	int			len_untill_nl;
	static int	eof_reached;
	
	next_line = NULL;
	i = 1;
	if (eof_reached || BUFFER_SIZE < 0)
		return (NULL);
/* 	if (strlen_untill(&buffer[0],'\n') < buffer + BUFFER_SIZE)
		 buffer = memncpy(buffer + strlen_untill(&buffer[0],'\n'); 
		 next_line = realloc_by_buffer(next_line, strlen_untill .. );
		 next_line = memncpy buffer -->  strlen_untill( ...
		 */

	while (!contains_endl_or_eof(buffer) || eof_reached)
	{
			//printf("\n\n----------------\nboucle %ld\n", i );
			//printf("allocation de next_line : %ld\n",( BUFFER_SIZE * i) + 1);
		next_line = realloc_by_buffer(next_line, (BUFFER_SIZE * i) + 1 );
		{
			//printf("next_line : \"%s\"\n", next_line);
			//write(1,"ancien buffer :\"", 16 );
			//write(1,buffer, BUFFER_SIZE );
			//write(1,"\"\n",2);
			//printf("strlcat ..\n");
		}
			
   		ft_strlcat(next_line, buffer, (BUFFER_SIZE * i) + 1);
		{	
			//printf("next_line : \"%s\"\n", next_line);
		}
		eof_reached = !read(fd, buffer, BUFFER_SIZE);
			//write(1,"nouveau buffer :\"", 17 );
			//write(1,buffer, BUFFER_SIZE );
			//write(1,"\"\n\n",3);
		i++;
	}
		//printf("\n\n----------------\nboucle %ld (fin)\n", i );
		//if (next_line)
			//printf("ft_strlen(next_line) : %ld \n", ft_strlen(next_line) );
		len_untill_nl = strlen_untill(&buffer[0],'\n') +1;

		//printf("len_untill_nl : %d\n", len_untill_nl);
		//write(1,"nouveau buffer :\"", 17 );
		//write(1,buffer, BUFFER_SIZE );
		//write(1,"\"\n\n",3);
		//printf("allocation de next_line : %ld\n", ft_strlen(next_line)
		//		+len_untill_nl);
	next_line = realloc_by_buffer(next_line, ft_strlen(next_line)
				+len_untill_nl);
	ft_strlcat(next_line, buffer, ft_strlen(next_line)
				+len_untill_nl);
		//printf("next_line : \"%s\"\n", next_line);

	ft_memcpy(buffer, buffer + len_untill_nl, BUFFER_SIZE - len_untill_nl );
		//write(1,"nouveau buffer :\"", 17 );
		//write(1,buffer, BUFFER_SIZE );
		//write(1,"\"\n\n",3);
	ft_memset(buffer +(BUFFER_SIZE - len_untill_nl), 0, len_untill_nl);
		//write(1,"nouveau buffer :\"", 17 );
		//write(1,buffer, BUFFER_SIZE );
		//write(1,"\"\n\n",3);
	return (next_line);
	}
