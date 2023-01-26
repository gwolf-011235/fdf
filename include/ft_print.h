/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:44:15 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/21 12:52:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <limits.h>
# include <unistd.h>
# include "ft_char.h"
# include "ft_num.h"
# include "ft_str.h"

typedef struct s_label {
	va_list	args;
	bool	hash;
	bool	plus;
	bool	space;
	bool	minus;
	bool	zero;
	int		width;
	int		precision;
	int		len;
	bool	neg;
	bool	empty;
	size_t	count;
}	t_label;

typedef void	(*t_ftptr)(t_label *, bool fastprint);

/* ft_printf */
int		ft_printf(const char *format, ...) \
			__attribute__ ((format (printf, 1, 2)));
bool	ft_check_string(t_label *label, const char *format);
bool	ft_check_conv(t_label *label, unsigned char c);
int		ft_check_flags(t_label *label, char c);
t_ftptr	ft_look_up_ptr(unsigned char c);

/* ft_printf_utils */
void	ft_init_label(t_label *label);
int		ft_check_sign_pos(t_label *label, char c);
int		ft_count_digits(long num, int base, unsigned long num2);
int		ft_check_padding(t_label *label);
int		ft_check_sign(t_label *label);

/* ft_put */
void	ft_putchar(unsigned char c, size_t *count);
void	ft_putstr(const char *s, size_t *count, int strlen);
void	ft_putnbr(long nbr, size_t *count);
void	ft_puthex(unsigned long nbr, size_t *count, char c);
void	ft_putptr(unsigned long nbr, size_t *count);

/* ft_conversion_c */
void	ft_convert_c(t_label *label, bool fastprint);
void	ft_print_c(t_label *label, unsigned char c);

/* ft_conversion_s */
void	ft_convert_s(t_label *label, bool fastprint);
int		ft_flags_s(t_label *label, const char *s);
void	ft_print_s(t_label *label, const char *s, int strlen);

/* ft_conversion_p */
void	ft_convert_p(t_label *label, bool fastprint);
void	ft_print_p(t_label *label, unsigned long num);

/* ft_conversion_i_d */
void	ft_convert_i(t_label *label, bool fastprint);
void	ft_flags_i(t_label *label, int num);
void	ft_print_i(t_label *label, int num, size_t *count);

/* ft_conversion_u */
void	ft_convert_u(t_label *label, bool fastprint);
void	ft_flags_u(t_label *label, unsigned int num);
void	ft_print_u(t_label *label, unsigned int num, size_t *count);

/* ft_conversion_x */
void	ft_convert_x(t_label *label, bool fastprint);
void	ft_flags_x(t_label *label, unsigned int num);
void	ft_print_x(t_label *label, unsigned int num, size_t *count);

/* ft_conversion_X */
void	ft_convert_x_big(t_label *label, bool fastprint);
void	ft_flags_x_big(t_label *label, unsigned int num);
void	ft_print_x_big(t_label *label, unsigned int num, size_t *count);

/* ft_conversion_percent */
void	ft_convert_percent(t_label *label, bool fastprint);

#endif
