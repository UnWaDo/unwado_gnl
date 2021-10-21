/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:58:46 by lalex             #+#    #+#             */
/*   Updated: 2021/10/21 14:14:26 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

typedef struct s_fdlst {
	int				fd;
	char			*buffer;
	struct s_fdlst	*next;
}	t_fdlst;

// Calculates the length of the zero-terminated string
// Returns the length of string without terminating null character
size_t	ft_strlen(const char *str);

// Returns the length of line, located in string `s`
// Returns 0 if `s` is NULL or there is no newline character
// Returns the length of line on success
size_t	ft_line_length(const char *s);

// Allocates memory for count objects of given size and filles it with zeros
// Returns pointer to allocated memory or NULL if allocation fails
void	*ft_calloc(size_t count, size_t size);

// Allocates new string with length ft_strlen(`str`) + `additional`
// Copies str to the beginning of new string
// Memory is allocated with ft_calloc
// If allocation fails, returns NULL, returns newly
// allocated string otherwise
// Old string must be freed manually
// Zero byte is not counted in `additional`
char	*ft_realloc_str(char *str, size_t additional);

// Moves bytes starting from index shift to the beginning
// of the buffer. Fills the buffer with zeros afterwards
void	shift_buffer(char *buffer, size_t shift);

// Searches for t_fdlst with fd `fd`
// If not found, creates new t_fdlst element and
// adds it to the beginning of `lst`
// Finally, allocates the buffer for t_fdlst
// of size BUFFER_SIZE + 1
// If allocation fails on any stage, the memory
// is freed and the NULL returns
t_fdlst	*prepare_cfd(int fd, t_fdlst **lst);

// Removes t_fdlst with fd `fd` from list and frees 
// `buffer` and itself
// If `*lst` is NULL, does nothing
// Always returns NULL
void	*pop_fd(t_fdlst **lst, int fd);

// Allocates string from `lst->buffer` including size symbols
// from the beginning. After this modify `lst->buffer` to begin
// with symbol [size + 1] and writing zero bytes until the end
// of initial string
// If allocation fails, does nothing and returns NULL
char	*pop_beginning(t_fdlst *lst, size_t size);

// Reallocates `cfd->buffer` increasing it's size
// to `ft_strlen(cfd->buffer)` + BUFFER_SIZE
// Sets the `line` to resulting line
// If read proceeds with less than BUFFER_SIZE
// unbing `buffer` from `cfd`, so the line can be
// used independently
// Returns 1 if read returns value less than BUFFER_SIZE
// and 0 in any other case
// `line` becomes NULL if allocation fails
// Returns `cfd->buffer` if no eof reached
int		read_more(t_fdlst *cfd, char **line);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif