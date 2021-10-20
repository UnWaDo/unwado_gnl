/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:05:34 by lalex             #+#    #+#             */
/*   Updated: 2021/10/20 18:50:11 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void simple_test()
{
	int		fd_read;
	int		fd_write;
	char	*line;
	int		i;

	fd_read = open("content", O_RDONLY);
	fd_write = open("res", O_WRONLY | O_CREAT | O_TRUNC);
	line = get_next_line(fd_read);
	i = 0;
	while (line)
	{
		write(fd_write, line, ft_strlen(line));
		free(line);
		line = get_next_line(fd_read);
	}
	close(fd_read);
	close(fd_write);
}

int	main(void)
{
	simple_test();
	return (0);
}
