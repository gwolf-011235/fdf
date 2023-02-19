/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:26:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/19 07:22:13 by gwolf            ###   ########.fr       */
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
# define RAD 0.01745329251
# define X 0
# define Y 1
# define Z 2
# define OFFSET_X 2
# define OFFSET_Y 3

# define D * 2
# define M + 1
# define P + 8

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

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

typedef float	t_mat4[4][4];

typedef struct s_vec3f {
	float	x;
	float	y;
	float	z;
}	t_vec3f;

typedef struct s_color {
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_rgba;

typedef struct s_point {
	int	x;
	int	y;
	int	color;
}	t_point;

typedef struct s_matinfo {
	float	scale;
	float	angle[3];
	float	translate[3];
	int		canvas[4];
}	t_props;

typedef struct s_map {
	t_vec3f	*points;
	t_vec3f	*morph;
	t_vec3f	*edges;
	int		*colors;
	t_point	*pixel;
	int		sum_points;
	char	filename[32];
	int		height;
	int		width;
	char	*rows[ROW_MAX];
	bool	hex;
	float	roll;
	float	pitch;
	float	yaw;
	float	scale;
	int		offset[2];
	float	trans_x;
	float	trans_y;
	int		min[3];
	int		max[3];	
	int		pattern[3];
	t_mat4	mat;
	t_props	props;
}	t_map;

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		size[2];
}	t_img;

typedef struct s_data {
	void	*mlx;
	void	*win;
	t_img	render;
	t_img	menu;
	t_map	map;
}	t_data;

//check.c
void	ft_check_map(t_map *map, char *filename);
int		ft_count_num_in_row(char *line, bool *hex);
void	ft_extract_rows(t_map *map, int fd);
void	ft_check_row(t_map *map, char *row);
void	ft_check_filename(t_map *map, char *filename);

//parse.c
void	ft_parse_map(t_map *map);
void	ft_map_alloc(t_map *map);
void	ft_parse_line(t_map *map, char *line, int index);
void	ft_set_colors(t_map *map, t_vec3f *points, int *colors);

//draw.c
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw_triangle(t_img *img, int x, int y, int size);
void	draw_square(t_img *img, int x, int y, int size, int trgb);
void	draw_line(t_img *img, t_point start, t_point end);
void	draw_points(t_img *img, t_map *map);
void	fill_background(t_img *img);
void	lines(t_img *img, t_map *map);
int		ft_is_inside(t_point point, int win_x, int win_y);
int		ft_is_outside(t_vec3f point, int canvas[2], float padding);
t_point	ft_convert_vec2point(t_vec3f point, int color);

//color.c
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		add_shade(double distance, int trgb);
int		get_opposite(int trgb);
int		gradient(int color_start, int color_end, double len, double pos);
int		ft_alpha_blend(int new_color, int old_color);

//hooks.c
int		mouse_hook(int button, int x, int y, t_data *data);
int		key_hook(int keycode, t_data *vars);
int		close_window(int keycode, t_data *vars);
int		mouse_move(int x, int y, void *param);

//window.c
void	testwindow(t_data *data);
void	ft_init_window(t_data *data);

//terminate.c
void	ft_terminate(char *message);
void	ft_free_rows(char *row, char *rows[ROW_MAX], int fd);
void	ft_free_map_ptr(t_map *map, char *string);
void	ft_free_mlx(t_data *data, char *string, bool error);

//matrix.c
void	ft_print_inverse(float inverse[4][8]);
void	ft_copy_mat4(const t_mat4 src, t_mat4 dest);
void	ft_build_transmat(t_mat4 mat, t_props props);
void	ft_mult_mat4(const t_mat4 first, const t_mat4 second, t_mat4 result);
void	ft_inverse_mat4(t_mat4 mat);
void	ft_init_mat4(t_mat4 matrix);
t_vec3f	ft_mult_vec3f_mat4(t_vec3f vec, t_mat4 mat);
void	rotate(t_vec3f *point, double ang_x, double ang_y, double ang_z);
t_vec3f	matrix_point(double mat[3][3], t_vec3f point);
void	project_2d(t_vec3f *point);
void	fill_mat4(t_mat4 matrix, t_vec3f *points);
void	lookat(t_vec3f from, t_vec3f to, t_vec3f up, t_mat4 cam2world);

//rotation.c
void	ft_rotate_x(t_mat4 trans, float roll);
void	ft_rotate_y(t_mat4 trans, float pitch);
void	ft_rotate_z(t_mat4 trans, float yaw);
void	ft_static_rotate(t_mat4 trans, int rotate);

//vector.c
void	vec3_normalize(t_vec3f *point);
t_vec3f	vec3_cross(t_vec3f a, t_vec3f b);
t_vec3f	vec3_subtract(t_vec3f a, t_vec3f b);

//reshape.c
void	ft_init_project(t_map *map);
void	ft_shape_map(t_map *map);
void	ft_redraw(t_data *data);
void	ft_init_pixel(t_vec3f *morph, int *colors, t_point *pixel, int sum);
void	ft_calc_points(t_vec3f *points, t_mat4 trans, int sum);

//map_utils.c
void	ft_map_init(t_map *map);
void	ft_find_extremes(t_map *map, int z);

//utils.c
int		ft_move_atoi(char *line);
int		ft_hex_to_decimal(char *line, int len);
int		ft_jump_over_hex(char *line);

//menu.c
void	ft_init_menu(t_data *data);

//print_utils.c
void	ft_print_mat4(t_mat4 matrix);
void	ft_print_point(t_vec3f point);
void	ft_print_inverse(float inverse[4][8]);

//box.c
void	ft_set_edges(t_map *map);
void	ft_morph_edges(t_vec3f *edges, t_mat4 trans);
void	ft_draw_box(t_data *data);
float	ft_fit_box(t_vec3f *edges, t_mat4 mat, t_props props);

//precalc_matrix.c
void	ft_const_iso(t_mat4 transmat);

//test.c
void	test(t_data *data);

#endif
