/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:08:51 by lalex             #+#    #+#             */
/*   Updated: 2021/10/23 13:08:56 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "per_line_test.h"

t_line	*create_line(char *line)
{
	t_line	*new;

	new = malloc(sizeof (*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->line = line;
	return (new);
}

void	append_line(t_line	**lines, t_line	*line)
{
	t_line	*last;

	last = *lines;
	while (last && last->next)
		last = last->next;
	if (last == NULL)
		*lines = line;
	else
		last->next = line;
}

void	clean_lines(t_line *line)
{
	t_line	*next;

	while (line)
	{
		if (line->line)
			free(line->line);
		next = line->next;
		free(line);
		line = next;
	}
}

int	compare_lists(t_line *lst1, t_line *lst2)
{
	if (lst1 == NULL || lst2 == NULL)
	{
		if (lst1 == lst2)
			return (0);
		else
			return (1);
	}
	while (lst1 && lst2)
	{
		if (lst1->line && lst2->line && strcmp(lst1->line, lst2->line))
			return (1);
		if ((lst1->line == NULL || lst2->line == NULL) && lst1->line != lst2->line)
			return (1);
		lst1 = lst1->next;
		lst2 = lst2->next;
	}
	if (lst1 != lst2)
		return (1);
	return (0);
}
