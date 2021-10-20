/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:05:34 by lalex             #+#    #+#             */
/*   Updated: 2021/10/20 21:10:25 by lalex            ###   ########.fr       */
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
		printf("Does not work with folders");
	}
	else
		printf("Grade: OK\n");
	close(fd_read);
}

int	main(void)
{
	directory_test();
	return (0);
}
