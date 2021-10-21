/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:59:05 by lalex             #+#    #+#             */
/*   Updated: 2021/10/21 14:12:02 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fdlst	*prepare_cfd(int fd, t_fdlst **lst)
{
	t_fdlst			*cfd;

	cfd = *lst;
	while (cfd)
	{
		if (cfd->fd == fd)
			break ;
		cfd = cfd->next;
	}
	if (!cfd)
	{
		cfd = ft_calloc(1, sizeof (*cfd));
		if (!cfd)
			return (NULL);
		cfd->fd = fd;
		if (*lst)
			cfd->next = *lst;
		*lst = cfd;
	}
	if (cfd->buffer == NULL)
		cfd->buffer = ft_calloc(((ssize_t) BUFFER_SIZE) + 1, 1);
	if (cfd->buffer == NULL)
		return (pop_fd(lst, fd));
	return (cfd);
}

void	*pop_fd(t_fdlst **lst, int fd)
{
	t_fdlst	*previous;
	t_fdlst	*current;

	current = *lst;
	while (current && current->fd != fd)
	{
		previous = current;
		current = current->next;
	}
	if (!current)
		return (NULL);
	if (current == *lst)
		*lst = current->next;
	else
		previous->next = current->next;
	if (current->buffer)
		free(current->buffer);
	free(current);
	return (NULL);
}

char	*pop_beginning(t_fdlst *lst, size_t size)
{
	char	*str;
	size_t	pos;

	if (lst == NULL || lst->buffer == NULL)
		return (NULL);
	str = ft_calloc(size + 1, sizeof (*str));
	if (!str)
		return (NULL);
	pos = 0;
	while (pos < size)
	{
		str[pos] = lst->buffer[pos];
		pos++;
	}
	shift_buffer(lst->buffer, size);
	return (str);
}

int	read_more(t_fdlst *cfd, char **line)
{
	ssize_t	length;
	size_t	buffer_len;	

	buffer_len = ft_strlen(cfd->buffer);
	if (buffer_len)
	{
		*line = ft_realloc_str(cfd->buffer, (ssize_t) BUFFER_SIZE);
		if (*line == NULL)
			return (0);
		free(cfd->buffer);
		cfd->buffer = *line;
	}
	length = read(cfd->fd, cfd->buffer + buffer_len, \
		(ssize_t) BUFFER_SIZE);
	*line = cfd->buffer;
	if (length < (ssize_t) BUFFER_SIZE)
	{
		if (ft_strlen(cfd->buffer))
			cfd->buffer = NULL;
		else
			*line = NULL;
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_fdlst	*fds;
	t_fdlst			*cfd;
	char			*line;
	size_t			line_len;

	if ((ssize_t) BUFFER_SIZE < 1 || (size_t) BUFFER_SIZE > (size_t) SSIZE_MAX)
		return (NULL);
	cfd = prepare_cfd(fd, &fds);
	if (!cfd)
		return (NULL);
	line_len = ft_line_length(cfd->buffer);
	if (line_len)
	{
		line = pop_beginning(cfd, line_len);
		if (!line)
			return (pop_fd(&fds, fd));
		return (line);
	}
	if (read_more(cfd, &line) || !line)
	{
		pop_fd(&fds, fd);
		return (line);
	}
	return (get_next_line(fd));
}
