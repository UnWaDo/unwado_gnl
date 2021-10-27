/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:50:57 by lalex             #+#    #+#             */
/*   Updated: 2021/10/27 19:55:42 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "files.h"

int	count_files(const char **input)
{
	size_t	len;

	len = 0;
	while (input[len])
		len++;
	return (len);
}

FILE	**get_files(const char **input)
{
	size_t	len;
	size_t	i;
	FILE	**files;

	len = count_files(input);
	files = malloc((len + 1) * sizeof (*files));
	if (!files)
		return (NULL);
	files[len] = NULL;
	i = 0;
	while (i < len)
	{
		files[i] = fopen(input[i], "r");
		if (files[i] == NULL)
		{
			close_files(files);
			return (NULL);
		}
		i++;
	}
	return (files);
}

int	*get_fds(const char **input)
{
	size_t	len;
	size_t	i;
	int		*fds;

	len = count_files(input);
	fds = malloc((len + 1) * sizeof (*fds));
	if (!fds)
		return (NULL);
	fds[len] = -1;
	i = 0;
	while (i < len)
	{
		fds[i] = open(input[i], O_RDONLY);
		if (fds[i] == -1)
		{
			while (i--)
				close(fds[i]);
			free(fds);
			return (NULL);
		}
		i++;
	}
	return (fds);
}

void	close_files(FILE **files)
{
	size_t	pos;

	pos = 0;
	while (files[pos])
	{
		fclose(files[pos]);
		pos++;
	}
	free(files);
}

void	close_fds(int *fds)
{
	size_t	pos;

	pos = 0;
	while (fds[pos])
	{
		close(fds[pos]);
		pos++;
	}
	free(fds);
}
