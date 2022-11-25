/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:17:21 by alevra            #+#    #+#             */
/*   Updated: 2022/11/24 17:55:55 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	strlen_until_gnl(char *str, char delimiter)
{
	size_t	len;

	len = 0;
	while (str && str[len] > 0 && str[len] != delimiter)
		len++;
	return (len);
}

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
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

void	*ft_memset_gnl(void *pointer, int value, size_t count)
{
	unsigned char	*ptr;
	size_t			i;

	if (count == 0)
		return (NULL);
	ptr = (unsigned char *)pointer;
	i = 0;
	while (i < count)
	{
		ptr[i] = value;
		i++;
	}
	return (pointer);
}

size_t	ft_strlcat_gnl(char *dst, const char *src, size_t size)
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
	while ((src[i] > 0) && (j + i + 1) < size)
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j != size)
		dst[j + i] = '\0';
	return (j + strlen_until_gnl((char *)src, 0));
}

char	*ft_realloc_gnl(char *oldstr, size_t newstr_size)
{
	char	*newstr;

	if (!newstr_size)
		newstr_size = 1;
	newstr = (char *)malloc(newstr_size * sizeof(char));
	if (!newstr)
		return (NULL);
	newstr = ft_memset_gnl(newstr, 0, newstr_size * sizeof(char));
	if (!newstr)
	{
		if (oldstr)
			free(oldstr);
		return (NULL);
	}
	if (oldstr)
	{
		ft_strlcat_gnl(newstr, oldstr, newstr_size);
		free(oldstr);
	}
	return (newstr);
}
