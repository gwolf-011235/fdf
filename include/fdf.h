/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:26:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/26 10:49:19 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
void draw_square(t_data *img, int x, int y, int size);

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

#endif
