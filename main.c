/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:05:34 by lalex             #+#    #+#             */
/*   Updated: 2021/10/16 14:02:55 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;
	int		i;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	printf("Buffer size: %d\nFile %d then %d and going around:\n", BUFFER_SIZE, fd1, fd2);
	line = get_next_line(fd1);
	i = 0;
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd2);
	}
	line = get_next_line(fd1);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd1);
	}
	close(fd1);
	close(fd2);
	return (0);
}
