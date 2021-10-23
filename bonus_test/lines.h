/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:52:39 by lalex             #+#    #+#             */
/*   Updated: 2021/10/23 13:52:40 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINES_H
# define LINES_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_line {
	char			*line;
	struct s_line	*next;
}	t_line;

t_line	*create_line(char *line);
void	append_line(t_line	**lines, t_line	*line);
void	clean_lines(t_line *line);
int		compare_lists(t_line *lst1, t_line *lst2);

#endif
