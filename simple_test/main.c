/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:05:34 by lalex             #+#    #+#             */
/*   Updated: 2021/10/21 14:37:11 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void simple_test(const char *input, const char *output)
{
	int		fd_read;
	int		fd_write;
	char	*line;
	int		i;

	fd_read = open(input, O_RDONLY);
	fd_write = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0666);
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

int	main(int argc, char **argv)
{
	if (argc < 3)
		simple_test("content", "res");
	else
		simple_test(argv[1], argv[2]);
	return (0);
}
