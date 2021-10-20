/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:59:05 by lalex             #+#    #+#             */
/*   Updated: 2021/10/21 00:03:29 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fdlst	*find_fd(t_fdlst *lst, int fd)
{
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
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
	while (lst->buffer[pos])
	{
		lst->buffer[pos - size] = lst->buffer[pos];
		lst->buffer[pos] = 0;
		pos++;
	}
	while (lst->buffer[pos - size])
	{
		lst->buffer[pos - size] = 0;
		pos++;
	}
	return (str);
}

t_fdlst	*prepare_cfd(int fd, t_fdlst **lst)
{
	t_fdlst			*cfd;

	cfd = find_fd(*lst, fd);
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
		cfd->buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (cfd->buffer == NULL)
		return (pop_fd(lst, fd));
	return (cfd);
}

char	*get_next_line(int fd)
{
	static t_fdlst	*fds;
	t_fdlst			*cfd;
	int				eof;
	char			*line;
	char			*newline;

	cfd = prepare_cfd(fd, &fds);
	if (!cfd)
		return (NULL);
	newline = ft_strchr(cfd->buffer, '\n');
	if (newline)
	{
		line = pop_beginning(cfd, newline - (cfd->buffer) + 1);
		if (!line)
			return (pop_fd(&fds, fd));
		return (line);
	}
	line = read_more(cfd, &eof);
	if (!line || eof)
	{
		pop_fd(&fds, fd);
		if (ft_strlen(line))
			return (line);
		return (NULL);
	}
	return (get_next_line(fd));
}
