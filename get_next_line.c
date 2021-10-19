/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:59:05 by lalex             #+#    #+#             */
/*   Updated: 2021/10/19 12:48:16 by lalex            ###   ########.fr       */
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

t_fdlst	*append_fd(t_fdlst **lst, int fd)
{
	t_fdlst	*new;

	new = ft_calloc(1, sizeof (*new));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buffer = ft_calloc(BUFFER_SIZE + 1, sizeof (*(new->buffer)));
	if (new->buffer == NULL)
	{
		free(new);
		return (NULL);
	}
	if (*lst)
		new->next = *lst;
	*lst = new;
	return (new);
}

void	pop_fd(t_fdlst **lst, int fd)
{
	t_fdlst	*previous;
	t_fdlst	*found;

	if (*lst == NULL)
		return ;
	found = NULL;
	if ((*lst)->fd == fd)
		found = *lst;
	previous = *lst;
	while (!found && previous->next)
	{
		if ((previous->next)->fd == fd)
		{
			found = previous->next;
			break ;
		}
		previous = (previous->next);
	}
	if (!found)
		return ;
	if (found == *lst)
		*lst = found->next;
	else
		previous->next = found->next;
	if (found->buffer)
		free(found->buffer);
	free(found);
}

char	*pop_beginning(t_fdlst *lst, size_t size)
{
	char	*str;
	size_t	pos;

	if (!lst)
		return (NULL);
	if (lst->buffer == NULL)
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
		pos++;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static t_fdlst	*fds;
	t_fdlst			*cfd;
	ssize_t			length;
	char			*line;
	char			*newline;

	cfd = find_fd(fds, fd);
	if (!cfd)
		cfd = append_fd(&fds, fd);
	if (!cfd)
		return (NULL);
	if (cfd->buffer == NULL)
		cfd->buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (cfd->buffer == NULL)
	{
		pop_fd(&fds, fd);
		return (NULL);
	}
	newline = ft_strchr(cfd->buffer, '\n');
	if (newline)
	{
		line = pop_beginning(cfd, newline - (cfd->buffer) + 1);
		return (line);
	}
	if (ft_strlen(cfd->buffer))
	{
		line = ft_realloc_str(cfd->buffer, BUFFER_SIZE);
		if (!line)
		{
			pop_fd(&fds, fd);
			return (NULL);
		}
		free(cfd->buffer);
		cfd->buffer = line;
	}
	length = read(fd, cfd->buffer + ft_strlen(cfd->buffer), BUFFER_SIZE);
	if (length < 1)
	{
		pop_fd(&fds, fd);
		return (NULL);
	}
	return (get_next_line(fd));
}
