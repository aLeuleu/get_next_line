/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:42:41 by alevra            #+#    #+#             */
/*   Updated: 2022/11/16 01:19:39 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*get_next_line(int fd);

//todo : comprendre ou ca bloque mdr

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
    get_next_line(fd);
	printf("************\n\n\n");
	printf("6 : %s\n", get_next_line(fd));
	printf("************\n\n\n");
}