/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:42:41 by alevra            #+#    #+#             */
/*   Updated: 2022/11/17 00:42:25 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

int	main(int argc, char const *argv[])
{

	int	fd;

	fd = open("./mon_fichier.txt", O_RDONLY);

	printf("1 : \"%s\"\n", get_next_line(fd));
	printf("2 : \"%s\"\n", get_next_line(fd));
	printf("3 : \"%s\"\n", get_next_line(fd));
	printf("4 : \"%s\"\n", get_next_line(fd));
	printf("5 : \"%s\"\n", get_next_line(fd));
	printf("6 : \"%s\"\n", get_next_line(fd));
    printf("7 : \"%s\"\n", get_next_line(fd));
    printf("8 : \"%s\"\n", get_next_line(fd));
    printf("9 : \"%s\"\n", get_next_line(fd));
    printf("10: \"%s\"\n", get_next_line(fd));
    printf("11: \"%s\"\n", get_next_line(fd));
}