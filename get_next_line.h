/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:58:46 by lalex             #+#    #+#             */
/*   Updated: 2021/10/19 12:48:18 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
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

// Searches for t_fdlst with `fd` as fd
// Returns pointer to found element
// or NULL if not list element has fd `fd`
t_fdlst	*find_fd(t_fdlst *lst, int fd);

// Creates new t_fdslt and allocates buffer of size
// BUFFER_SIZE + 1
// Returns NULL if allocation fails (either while
// allocating t_fdlst or while allocating buffer)
// Newly allocated element is put at the beginning of `lst`
t_fdlst	*append_fd(t_fdlst **lst, int fd);

// Removes t_fdlst with fd `fd` from list and frees 
// `buffer` and itself
// If `*lst` is NULL, does nothing
void	pop_fd(t_fdlst **lst, int fd);

// Allocates string from `lst->buffer` including size symbols
// from the beginning. After this modify `lst->buffer` to begin
// with symbol [size + 1] and writing zero bytes until the end
// of initial string
// If allocation fails, does nothing and returns NULL
char	*pop_beginning(t_fdlst *lst, size_t size);

// Returns pointer to first location of character `c` in string `s`
// Returns NULL if character does not appear in string
char	*ft_strchr(const char *s, int c);

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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif