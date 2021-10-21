/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:05:34 by lalex             #+#    #+#             */
/*   Updated: 2021/10/21 14:46:31 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void directory_test()
{
	int		fd_read;
	char	*line;

	fd_read = open("directory_test", O_RDONLY);
	line = get_next_line(fd_read);
	if (line)
	{
		free(line);
		printf("\033[0;31mDoes not work with folders\033[0m\n");
	}
	else
		printf("\033[0;32mGrade: OK\033[0m\n");
	close(fd_read);
}

int	main(void)
{
	directory_test();
	return (0);
}
