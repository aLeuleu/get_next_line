/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:52:45 by alevra            #+#    #+#             */
/*   Updated: 2022/11/17 11:39:06 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
int     strlen_untill(char *str, char delimiter);
void    *ft_memcpy(void *dest, const void *src, size_t n);
void    *ft_memset(void *pointer, int value, size_t count);
size_t  ft_strlcat(char *dst, const char *src, size_t size);
char    *ft_realloc(char *oldstr, size_t newstr_size);

#endif