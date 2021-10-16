/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:06:44 by lalex             #+#    #+#             */
/*   Updated: 2021/10/16 13:11:13 by lalex            ###   ########.fr       */
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	pos;
	size_t	len;

	len = ft_strlen(src);
	if (!dstsize)
		return (len);
	pos = 0;
	dstsize--;
	while (pos < len && pos < dstsize)
	{
		dst[pos] = src[pos];
		pos++;
	}
	dst[pos] = '\0';
	return (len);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(s1) + 1;
	copy = malloc(sizeof(*copy) * len);
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s1, len);
	return (copy);
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

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	byte;
	unsigned char	*b_char;
	size_t			i;

	byte = (unsigned char) c;
	b_char = b;
	i = 0;
	while (i < len)
	{
		b_char[i] = byte;
		i++;
	}
	return (b);
}
