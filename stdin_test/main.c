/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:05:34 by lalex             #+#    #+#             */
/*   Updated: 2021/10/20 19:28:12 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void stdin_test()
{
	char	*line;
	int		i;

	line = get_next_line(0);
	i = 0;
	while (line)
	{
		printf("\nLine: %s\n", line);
		free(line);
		line = get_next_line(0);
	}
}

int	main(void)
{
	printf("Buffer size: %d\n", BUFFER_SIZE);
	stdin_test();
	return (0);
}
