/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:18:16 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/21 11:24:41 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FD_H
# define FT_FD_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdbool.h>
# include "ft_str.h"
# include "ft_mem.h"

/* buffer size for get_next_line */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# elif BUFFER_SIZE <= 0
#  error "BUFFER_SIZE must be bigger than 0"
# endif

/* list for get_next_line */
typedef struct s_buf_node {
	char				buf[BUFFER_SIZE];
	size_t				size;
	bool				has_nl;
	struct s_buf_node	*next;
	struct s_buf_node	*tail;
}				t_buf_node;

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* get_next_line */
char		*get_next_line(int fd);

/* get_next_line_utils */
char		*ft_lstclear_plus(t_buf_node **head, bool fclear);
t_buf_node	*ft_lstadd_buf(t_buf_node **head);

#endif
