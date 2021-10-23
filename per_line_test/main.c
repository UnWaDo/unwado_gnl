/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:05:34 by lalex             #+#    #+#             */
/*   Updated: 2021/10/23 13:48:21 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "per_line_test.h"
#include <fcntl.h>
#include <stdio.h>

static t_line	*read_file(const char *input)
{
	t_line	*lines;
	t_line	*new;
	char	*line;
	size_t	len;
	FILE	*file;

	file = fopen(input, "r");
	if (file == NULL)
		return (NULL);
	lines = NULL;
	line = NULL;
	len = 0;
	while (getline(&line, &len, file) != -1)
	{
		new = create_line(line);
		if (!new)
		{
			if (line)
				free(line);
			clean_lines(lines);
			return (NULL);
		}
		line = NULL;
		len = 0;
		append_line(&lines, new);
	}
	new = create_line(NULL);
	if (!new)
	{
		if (line)
			free(line);
		clean_lines(lines);
		return (NULL);
	}
	append_line(&lines, new);
	if (line)
		free(line);
	fclose(file);
	return (lines);
}

static t_line	*read_file_by_gnl(const char *input)
{
	t_line	*lines;
	t_line	*new;
	char	*line;
	int		fd;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		return (NULL);
	lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		new = create_line(line);
		if (!new)
		{
			if (line)
				free(line);
			clean_lines(lines);
			return (NULL);
		}
		append_line(&lines, new);
		line = get_next_line(fd);
	}
	new = create_line(NULL);
	if (!new)
	{
		if (line)
			free(line);
		clean_lines(lines);
		return (NULL);
	}
	append_line(&lines, new);
	if (line)
		free(line);
	close(fd);
	return (lines);
}

static void per_line_test(const char *input)
{
	t_line	*user;
	t_line	*system;

	system = read_file(input);
	user = read_file_by_gnl(input);
	if (compare_lists(system, user))
		printf("\033[0;31m%s: KO\033[0m\n", input);
	else
		printf("\033[32m%s: OK\033[0m\n", input);
	clean_lines(user);
	clean_lines(system);
}

int	main(void)
{
	per_line_test("texts/empty");
	per_line_test("texts/short_line");
	per_line_test("texts/short_no_nl");
	per_line_test("texts/single_newline");
	per_line_test("texts/43_with_nl");
	per_line_test("texts/several_lines");
	per_line_test("texts/long_text");
	return (0);
}
