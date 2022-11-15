/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:02:39 by alevra            #+#    #+#             */
/*   Updated: 2022/11/15 18:38:51 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

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

static int	contains_endl(char *str)
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
#include <stdio.h>

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
	int			len_untill_nl_or_eof;
	
	next_line = NULL;
	i = 1;
/* 	if (strlen_untill(&buffer[0],'\n') < buffer + BUFFER_SIZE)
		 buffer = memncpy(buffer + strlen_untill(&buffer[0],'\n'); 
		 next_line = realloc_by_buffer(next_line, strlen_untill .. );
		 next_line = memncpy buffer -->  strlen_untill( ...
		 */

	while (!contains_endl(buffer) && i < 10)
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
		read(fd, buffer, BUFFER_SIZE);
			//write(1,"nouveau buffer :\"", 17 );
			//write(1,buffer, BUFFER_SIZE );
			//write(1,"\"\n\n",3);
		i++;
	}
		//printf("\n\n----------------\nboucle %ld (fin)\n", i );
		//if (next_line)
			//printf("ft_strlen(next_line) : %ld \n", ft_strlen(next_line) );
	len_untill_nl_or_eof = strlen_untill(&buffer[0],'\n') +1;
		//printf("len_untill_nl_or_eof : %d\n", len_untill_nl_or_eof);

		//printf("allocation de next_line : %ld\n", ft_strlen(next_line)
		//		+len_untill_nl_or_eof);
	next_line = realloc_by_buffer(next_line, ft_strlen(next_line)
				+len_untill_nl_or_eof);
	ft_strlcat(next_line, buffer, ft_strlen(next_line)
				+len_untill_nl_or_eof);
		//printf("next_line : \"%s\"\n", next_line);

	ft_memcpy(buffer, buffer + len_untill_nl_or_eof, BUFFER_SIZE - len_untill_nl_or_eof );
		//write(1,"nouveau buffer :\"", 17 );
		//write(1,buffer, BUFFER_SIZE );
		//write(1,"\"\n\n",3);
	ft_memset(buffer +(BUFFER_SIZE - len_untill_nl_or_eof), 0, len_untill_nl_or_eof);
		//write(1,"nouveau buffer :\"", 17 );
		//write(1,buffer, BUFFER_SIZE );
		//write(1,"\"\n\n",3);
	return (next_line);
	}


int	main(int argc, char const *argv[])
{
	int	fd;

	fd = open("./mon_fichier.txt", O_RDONLY);
	printf("1 : %s\n", get_next_line(fd));
	printf("************\n\n\n");
	printf("2 : %s\n", get_next_line(fd));
	printf("************\n\n\n");
	printf("3 : %s\n", get_next_line(fd));
	printf("************\n\n\n");
	printf("4 : %s\n", get_next_line(fd));
	printf("************\n\n\n");
	printf("5 : %s\n", get_next_line(fd));
	printf("************\n\n\n");
	printf("6 : %s\n", get_next_line(fd));
	printf("************\n\n\n");
}
// todo gerer les cas ou le file est deja entierement read
// ca ne sert a rien de faire un fd status si on a perdu ce que l'on a lu apres le \n ! .. il faut sauvegarder ca quelque part .......