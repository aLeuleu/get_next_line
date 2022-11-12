/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:02:39 by alevra            #+#    #+#             */
/*   Updated: 2022/11/12 11:23:59 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

typedef int (*pfn_contains_endl)(char *str);

typedef struct s_buff
{
	char *str;
	pfn_contains_endl contains_endl;
} t_buff;

int     contains_endl(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		if (str[i] == 'n' || str[i++] == '\t')
			return(1);
	return (0);
}

char	*read_buffer(int fd, size_t buffer_size)
{
	char *buff;

	buff = (char *)malloc(sizeof(char)* buffer_size);
	read(fd,buff, buffer_size - 1);
	buff[buffer_size] = '\0';
	return (buff);
}



#include <stdio.h>
#include <fcntl.h>



int main(int argc, char const *argv[])
{
	int fd = open("./mon_fichier.txt", O_RDONLY);

	t_buff BUFF;

	BUFF.contains_endl = &contains_endl;
	BUFF.str = read_buffer(fd, 150);
	printf("%d\n", BUFF.contains_endl(BUFF.str));

	return 0;
}
