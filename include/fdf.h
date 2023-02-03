/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:26:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/03 11:32:12 by gwolf            ###   ########.fr       */
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
# include <math.h>

# include "mlx.h"
# include "ft_fd.h"
# include "ft_str.h"
# include "ft_print.h"
# include "ft_char.h"
# include "ft_num.h"
# include "ft_mem.h"
# include "err_message.h"

# define ROW_MAX 100

# define WIN_X 1920
# define WIN_Y 1080

# define COLOR_TOP 0xFF0000
# define COLOR_MID 0xFFFFFF
# define COLOR_LOW 0x0000FF

# define KEY_ARROW_LEFT 65361
# define KEY_ARROW_UP 65362
# define KEY_ARROW_RIGHT 65363
# define KEY_ARROW_DOWN 65364

typedef struct s_point {
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point;

typedef struct s_po_int {
	int	x;
	int y;
}	t_po_int;

typedef struct s_map {
	t_point	*points;
	t_point	*morph;
	int		height;
	int		width;
	int		sum_points;
	char	*rows[ROW_MAX];
	double	ang_x;
	double	ang_y;
	double	ang_z;
	double	scale;
	double	offset_x;
	double	offset_y;
	int		top;
	int		low;
	int		color_top;
	int		color_mid;
	int		color_low;
}	t_map;

typedef struct s_img {
	void *img;
	char *addr;
	int bit_per_pixel;
	int line_length;
	int endian;
}	t_img;

typedef struct s_data {
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	map;
}	t_data;

//draw.c
void my_mlx_pixel_put(t_img *data, int x, int y, int color);
void draw_triangle(t_img *img, int x, int y, int size);
void draw_square(t_img *img, int x, int y, int size, int trgb);
void draw_line(t_img *img, t_po_int start, t_po_int end, int color) ;
void draw_points(t_img *img, t_map *map);
void	fill_background(t_img *img);
void	lines(t_img *img, t_map *map);
int	ft_is_outside(t_point point);

//color.c
int create_trgb(int t, int r, int g, int b);
int get_t(int trgb);
int get_r(int trgb);
int get_g(int trgb);
int get_b(int trgb);
int add_shade(double distance, int trgb);
int get_opposite(int trgb);
int	gradient(int color_start, int color_end, double len, double pos);

//hooks.c
int key_hook(int keycode, t_data *vars);
int close_window(int keycode, t_data *vars);
int mouse_hook(int button, int x, int y, void *param);
int mouse_move(int x, int y, void *param);

//testwin.c
void testwindow(t_data *data);

//error.c
void	terminate(char *message);

//parse.c
int	ft_count_num(char *line);
void	map_alloc(t_map *map, int fd);
void	ft_convert_line(t_map *map, char *line, int index);
void	fetch_points(t_map *map);
void	parse_map(t_map *map, char *filename);

//matrix.c
void	mat_mult(double first[3][3], double second[3][3], double mul[3][3]);
void	rotate(t_point *point, double ang_x, double ang_y, double ang_z);
t_point	matrix_point(double mat[3][3], t_point point);
t_point	project_2d(t_point point);

//reshape.c
void	ft_shape_map(t_map *map);
void	ft_redraw(t_data *data);

//map_utils.c
void	ft_map_init(t_map *map);
void	ft_find_extremes(t_map *map, int z);
void	ft_copy_map(t_map *map);

#endif
