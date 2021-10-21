/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:06:44 by lalex             #+#    #+#             */
/*   Updated: 2021/10/21 13:23:38 by lalex            ###   ########.fr       */
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

size_t	ft_line_length(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	if (s[len] == '\n')
		return (len + 1);
	return (0);
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

void	shift_buffer(char *buffer, size_t shift)
{
	size_t	pos;

	pos = shift;
	while (buffer[pos])
	{
		buffer[pos - shift] = buffer[pos];
		buffer[pos] = 0;
		pos++;
	}
	while (buffer[pos - shift])
	{
		buffer[pos - shift] = 0;
		pos++;
	}
}
