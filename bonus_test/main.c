/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:05:34 by lalex             #+#    #+#             */
/*   Updated: 2021/10/27 20:25:58 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "lines.h"
#include "files.h"
#include <stdlib.h>
#include <stdio.h>

static size_t	count_files(FILE **files)
{
	size_t	len;

	len = 0;
	while (files[len])
		len++;
	return (len);
}

static size_t	count_fds(int *fds)
{
	size_t	len;

	len = 0;
	while (fds[len] != -1)
		len++;
	return (len);
}

int	*create_eofs(size_t len)
{
	int	*eofs;

	eofs = malloc(len * sizeof (*eofs));
	if (!eofs)
		return (NULL);
	while (len--)
		eofs[len] = 0;
	return (eofs);
}

int	is_all_read(int *eofs, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count && eofs[i] == 1)
		i++;
	if (i < count)
		return (0);
	return (1);
}

t_line	*read_files(FILE **files)
{
	t_line	*lines;
	t_line	*new;
	char	*line;
	size_t	line_length;
	size_t	files_number;
	size_t	files_iterator;
	int		*eofs;

	files_number = count_files(files);
	eofs = create_eofs(files_number);
	if (!eofs)
		return (NULL);
	lines = NULL;
	line_length = 0;
	do {
		files_iterator = 0;
		while (files_iterator < files_number)
		{
			if (eofs[files_iterator])
			{
				files_iterator++;
				continue ;
			}
			line = NULL;
			line_length = 0;
			if (getline(&line, &line_length, files[files_iterator]) == -1)
			{
				if (line)
					free(line);
				line = NULL;
				eofs[files_iterator] = 1;
			}
			new = create_line(line);
			if (!new)
			{
				if (line)
					free(line);
				clean_lines(lines);
				free(eofs);
				return (NULL);
			}
			append_line(&lines, new);
			files_iterator++;
		}
	} while (is_all_read(eofs, files_number) == 0);
	if (line)
		free(line);
	free(eofs);
	return (lines);
}

t_line	*read_files_by_gnl(int *fds)
{
	t_line	*lines;
	t_line	*new;
	char	*line;
	size_t	fds_number;
	size_t	fds_iterator;
	int		*eofs;

	fds_number = count_fds(fds);
	eofs = create_eofs(fds_number);
	if (!eofs)
		return (NULL);
	lines = NULL;
	do {
		fds_iterator = 0;
		while (fds_iterator < fds_number)
		{
			if (eofs[fds_iterator])
			{
				fds_iterator++;
				continue ;
			}
			line = get_next_line(fds[fds_iterator]);
			if (!line)
				eofs[fds_iterator] = 1;
			new = create_line(line);
			if (!new)
			{
				if (line)
					free(line);
				clean_lines(lines);
				free(eofs);
				return (NULL);
			}
			append_line(&lines, new);
			fds_iterator++;
		}
	} while (is_all_read(eofs, fds_number) == 0);
	if (line)
		free(line);
	free(eofs);
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
