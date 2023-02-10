/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:26:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/10 09:58:11 by gwolf            ###   ########.fr       */
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

# define ROW_MAX 1000

# define COLOR_TOP 0xFF0000
# define COLOR_MID 0x00FF00
# define COLOR_LOW 0x0000FF

# define KEY_ARROW_LEFT 65361
# define KEY_ARROW_UP 65362
# define KEY_ARROW_RIGHT 65363
# define KEY_ARROW_DOWN 65364
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_F 102
# define KEY_G 103
# define KEY_H 104
# define KEY_Q 113
# define KEY_W 119

typedef double t_mat4[4][4]; 

typedef struct s_vec3f {
	float	x;
	float	y;
	float	z;
}	t_vec3f;

typedef struct s_vec2i {
	int	x;
	int y;
}	t_vec2i;

typedef struct s_map {
	t_vec3f	*points;
	t_vec3f	*morph;
	int		*color_array;
	char	filename[32];
	int		height;
	int		width;
	int		sum_points;
	char	*rows[ROW_MAX];
	bool	hex;
	float	ang_x;
	float	ang_y;
	float	ang_z;
	float	scale;
	int		offset_x;
	int		offset_y;
	float	trans_x;
	float	trans_y;
	int		top;
	int		low;
	int		color_top;
	int		color_mid;
	int		color_low;
}	t_map;

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		win_x;
	int		win_y;
}	t_img;

typedef struct s_data {
	void	*mlx;
	void	*win;
	t_img	render;
	t_img	menu;
	t_map	map;
}	t_data;

//validate.c
void	ft_validate_map(t_map *map, char *filename);
void	ft_count_num_in_row(char *line, int *count, bool *hex);
int		ft_jump_over_hex(char *line);
void	ft_extract_rows(t_map *map, int fd);
void	ft_check_row(t_map *map, char *row);
void	ft_validate_filename(t_map *map, char *filename);

//parse.c
void	ft_parse_map(t_map *map);
void	ft_map_alloc(t_map *map);
void	ft_parse_line(t_map *map, char *line, int index);
void	ft_set_colors(t_map *map);

//draw.c
void my_mlx_pixel_put(t_img *data, int x, int y, int color);
void draw_triangle(t_img *img, int x, int y, int size);
void draw_square(t_img *img, int x, int y, int size, int trgb);
void	draw_line(t_img *img, t_vec2i start, t_vec2i end, int colors[2]);
void draw_points(t_img *img, t_map *map);
void	fill_background(t_img *img);
void	lines(t_img *img, t_map *map);
int	ft_is_outside(t_vec3f point, int win_x, int win_y);
t_vec2i	ft_convert_3to2(t_vec3f point);

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

//window.c
void testwindow(t_data *data);
void	ft_init_window(t_data *data);

//error.c
void	terminate(char *message);

//matrix.c
void	mat_mult(double first[3][3], double second[3][3], double mul[3][3]);
void	rotate(t_vec3f *point, double ang_x, double ang_y, double ang_z);
t_vec3f	matrix_point(double mat[3][3], t_vec3f point);
void	project_2d(t_vec3f *point);
void	fill_mat4(t_mat4 matrix, t_vec3f *points);
void	lookat(t_vec3f from, t_vec3f to, t_vec3f up, t_mat4 cam2world);

//vector.c
void	vec3_normalize(t_vec3f *point);
t_vec3f	vec3_cross(t_vec3f a, t_vec3f b);
t_vec3f	vec3_subtract(t_vec3f a, t_vec3f b);

//reshape.c
void	ft_shape_map(t_map *map);
void	ft_redraw(t_data *data);

//map_utils.c
void	ft_map_init(t_map *map);
void	ft_find_extremes(t_map *map, int z);
void	ft_copy_map(t_map *map);

//utils.c
int	ft_move_atoi(char *line);
int	ft_hex_to_decimal(char *line, int len);

//menu.c
void	ft_init_menu(t_data *data);

//test.c
void	test(t_data *data);

#endif
