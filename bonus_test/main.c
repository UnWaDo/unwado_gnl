/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:05:34 by lalex             #+#    #+#             */
/*   Updated: 2021/10/23 14:11:54 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "lines.h"
#include "files.h"
#include <stdlib.h>
#include <stdio.h>

t_line	*read_files(FILE **files)
{
	t_line	*lines;
	t_line	*new;
	char	*line;
	size_t	len;
	size_t	pos;
	int		some_non_empty;

	lines = NULL;
	line = NULL;
	len = 0;
	do {
		some_non_empty = 0;
		pos = 0;
		while (files[pos])
		{
			if (getline(&line, &len, files[pos]) != -1)
				some_non_empty = 1;
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
			pos++;
		}
	} while (some_non_empty);
	if (line)
		free(line);
	return (lines);
}

t_line	*read_files_by_gnl(int *fds)
{
	t_line	*lines;
	t_line	*new;
	char	*line;
	size_t	pos;
	int		some_non_empty;

	lines = NULL;
	do {
		some_non_empty = 0;
		pos = 0;
		while (fds[pos] != -1)
		{
			line = get_next_line(fds[pos]);
			if (line)
				some_non_empty = 1;
			new = create_line(line);
			if (!new)
			{
				if (line)
					free(line);
				clean_lines(lines);
				return (NULL);
			}
			append_line(&lines, new);
			pos++;
		}
	} while (some_non_empty);
	if (line)
		free(line);
	return (lines);
}

void bonus_test(const char **input)
{
	t_line	*user;
	t_line	*system;
	FILE	**files;
	int		*fds;

	files = get_files(input);
	if (files == NULL)
	{
		printf("\033[0;31mUnexpected error. \
			Make sure you launch test from right directory\033[0m\n");
		exit(EXIT_FAILURE);

	}
	system = read_files(files);
	close_files(files);
	fds = get_fds(input);
	if (fds == NULL)
	{
		printf("\033[0;31mUnexpected error. \
			Make sure you launch test from right directory\033[0m\n");
		exit(EXIT_FAILURE);

	}
	user = read_files_by_gnl(fds);
	close_fds(fds);
	if (compare_lists(system, user))
		printf("\033[0;31mMultiple FD: KO\033[0m\n");
	else
		printf("\033[32mMultiple FD: OK\033[0m\n");
	clean_lines(user);
	clean_lines(system);
}

int	main(void)
{
	char	*files[] = {
		"texts/empty",
		"texts/short_line",
		"texts/short_no_nl",
		"texts/single_newline",
		"texts/43_with_nl",
		"texts/several_lines",
		"texts/long_text",
		NULL
	};

	bonus_test((const char **) files);
	return (0);
}
