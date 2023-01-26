/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:26:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/26 18:02:35 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# include "mlx.h"
# include "ft_fd.h"
# include "ft_str.h"
# include "ft_print.h"
# include "ft_char.h"
# include "ft_num.h"
# include "err_message.h"

# define ROW_MAX 100

typedef struct s_map {
	int *array;
	int height;
	int width;
	char *rows[ROW_MAX];
}	t_map;

typedef struct s_data {
	void *img;
	char *addr;
	int bit_per_pixel;
	int line_length;
	int endian;
}	t_data;

typedef struct s_vars {
	void *mlx;
	void *win;
}	t_vars;

//draw.c
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_triangle(t_data *img, int x, int y, int size);
void draw_square(t_data *img, int x, int y, int size, int trgb);

//color.c
int create_trgb(int t, int r, int g, int b);
int get_t(int trgb);
int get_r(int trgb);
int get_g(int trgb);
int get_b(int trgb);
int add_shade(double distance, int trgb);
int get_opposite(int trgb);

//hooks.c
int key_hook(int keycode, t_vars *vars);
int close_window(int keycode, t_vars *vars);
int mouse_hook(int button, int x, int y, void *param);
int mouse_move(int x, int y, void *param);

//testwin.c
void testwindow(void);

//error.c
void	terminate(char *message);

#endif
