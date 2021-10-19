/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:06:44 by lalex             #+#    #+#             */
/*   Updated: 2021/10/19 12:48:15 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	char	search;

	search = (char) c;
	while (*s)
	{
		if (*s == search)
			return ((char *) s);
		s++;
	}
	if (*s == search)
		return ((char *) s);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;
	size_t	len;

	len = count * size;
	res = malloc(len);
	if (!res)
		return (NULL);
	while (len--)
		res[len] = 0;
	return (res);
}

char	*ft_realloc_str(char *str, size_t additional)
{
	size_t	length;
	size_t	pos;
	char	*copy;

	length = ft_strlen(str);
	copy = ft_calloc(length + additional + 1, sizeof (*copy));
	if (!copy)
		return (NULL);
	pos = 0;
	while (pos < length)
	{
		copy[pos] = str[pos];
		pos++;
	}
	return (copy);
}
