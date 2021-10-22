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

void	read_more(t_fdlst *cfd)
{
	ssize_t	length;

	if (cfd->buffer_size || cfd->buffer_shift)
		expand_buffer(cfd);
	if (cfd->buffer == NULL)
		return ;
	length = read(cfd->fd, cfd->buffer + \
		cfd->buffer_shift + cfd->buffer_size, \
		(size_t) BUFFER_SIZE);
	if (length > 0)
		cfd->buffer_size = cfd->buffer_size + length;
	cfd->buffer[cfd->buffer_shift + cfd->buffer_size] = 0;
}

char	*get_next_line(int fd)
{
	static t_fdlst	*fds;
	t_fdlst			*cfd;
	char			*line;

	if ((ssize_t) BUFFER_SIZE < 1 || (size_t) BUFFER_SIZE > (size_t) SSIZE_MAX)
		return (NULL);
	cfd = prepare_cfd(fd, &fds);
	if (!cfd)
		return (NULL);
	line = NULL;
	while (!line)
	{
		scan_buffer(cfd);
		if (cfd->line_length && \
			cfd->buffer[cfd->buffer_shift + cfd->line_length - 1] == '\n')
			break ;
		read_more(cfd);
		if (cfd->line_length == cfd->buffer_size)
			break ;
	}
	if (cfd->line_length)
		line = pop_line(cfd);
	if (!line)
		pop_fd(&fds, fd);
	return (line);
}
