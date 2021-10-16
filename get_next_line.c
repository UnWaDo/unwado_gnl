/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:59:05 by lalex             #+#    #+#             */
/*   Updated: 2021/10/16 13:48:39 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Allocates a line from `s1`
// Return pointer to allocated line copy with newline character
// Returns NULL if allocation fails or if newline character is not found
char	*ft_linedup(const char *s1)
{
	size_t	len;
	char	*copy;

	len = 0;
	while (s1[len] != '\n' && s1[len])
		len++;
	if (s1[len] == 0)
		return (NULL);
	copy = malloc(sizeof(*copy) * (len + 2));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s1, len + 2);
	return (copy);
}

char	*ft_strdcat(char *str1, char *str2, void (*str_free)(char *, char *))
{
	char	*united;
	size_t	pos;
	size_t	pos2;

	united = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!united)
	{
		(*str_free)(str1, str2);
		return (NULL);
	}
	pos = 0;
	while (str1 && str1[pos])
	{
		united[pos] = str1[pos];
		pos++;
	}
	pos2 = 0;
	while (str2 && str2[pos2])
	{
		united[pos + pos2] = str2[pos2];
		pos2++;
	}
	united[pos + pos2] = 0;
	(*str_free)(str1, str2);
	return (united);
}

void	ft_free_both(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

char	*locate_line(char *buffer, size_t size, char **start)
{
	size_t	i;
	char	*end;

	*start = NULL;
	i = 0;
	while (buffer[i] == 0 && i < size)
		i++;
	if (i >= size)
		return (NULL);
	*start = buffer + i;
	end = buffer + i;
	while (*end != '\n' && *end)
		end++;
	if (*end)
		return (end);
	return (NULL);
}

void	*ft_memdup(void *start, size_t len)
{
	char	*mem;

	mem = malloc(len);
	if (!mem)
		return (NULL);
	while (len--)
		mem[len] = ((char *) start)[len];
	return (mem);
}

void	ft_check_read(ssize_t expected, ssize_t resulting, char *buffer)
{
	if (resulting == 0)
		ft_memset(buffer, 0, BUFFER_SIZE);
	if (resulting < expected)
		buffer[resulting] = 0;
}

#include <stdio.h>

// If `end` is NULL goes until the first zero byte
char	*ft_alloc_buffer(char *start, char *end, size_t buff_len)
{
	char	*copy;
	size_t	pos;
	size_t	length;

	if (!start)
		return (NULL);
	if (end && end < start)
		return (NULL);
	length = end - start + 1;
	if (!end)
		length = ft_strlen(start);
	if (length > buff_len)
		length = buff_len;
	copy = malloc(sizeof (*copy) * (length + 1));
	pos = 0;
	while (pos < length)
	{
		copy[pos] = start[pos];
		start[pos] = 0;
		pos++;
	}
	copy[length] = 0;
	return (copy);
}

char	*get_next_line(int fd)
{
	static char		BUFFER[BUFFER_SIZE];
	static int		last_fd = -1;
	char			*line;
	char			*line_start;
	char			*line_end;
	ssize_t			length;

	if (last_fd != fd)
		ft_memset(BUFFER, 0, BUFFER_SIZE);
	last_fd = fd;
	line_end = locate_line(BUFFER, BUFFER_SIZE, &line_start);
	line = ft_alloc_buffer(line_start, line_end, BUFFER + BUFFER_SIZE - line_start);
	while (line_end == NULL)
	{
		length = read(fd, BUFFER, BUFFER_SIZE - 1);
		ft_check_read(BUFFER_SIZE - 1, length, BUFFER);
		if (length == 0 || length == -1)
			return (line);
		line_end = locate_line(BUFFER, BUFFER_SIZE - 1, &line_start);
		line = ft_strdcat(line, ft_alloc_buffer(line_start, line_end, BUFFER + BUFFER_SIZE - line_start), &ft_free_both);
	}
	return (line);
}
