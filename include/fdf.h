/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:26:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/14 18:46:09 by gwolf            ###   ########.fr       */
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
# include <time.h>

# include "mlx.h"
# include "ft_fd.h"
# include "ft_str.h"
# include "ft_print.h"
# include "ft_char.h"
# include "ft_num.h"
# include "ft_mem.h"
# include "err_message.h"
# include "colors.h"
# include "X.h"
# include "key_macros.h"
# include "angles.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define ROW_MAX 1000
# define RAD 0.01745329251
# define X 0
# define Y 1
# define Z 2
# define LON 0
# define LAT 1
# define OFFSET_X 2
# define OFFSET_Y 3
# define XMAX 0
# define XMIN 1
# define YMAX 2
# define YMIN 3
# define ZMAX 4
# define ZMIN 5
# define TOP 1
# define ISO 2
# define NICE 3
# define MENU_WIDTH 320
# define MENU_HEIGHT 1080
# define OFF 0
# define STATS 1
# define CONTROL 2

typedef struct s_coord {
	float	lon;
	float	lat;
}	t_coord;

typedef struct s_color {
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_color;

typedef float	t_mat4[4][4];

typedef struct s_vec3f {
	float	x;
	float	y;
	float	z;
	int		color;
	bool	hidden;
}	t_vec3f;

typedef struct s_pixel {
	int	x;
	int	y;
	int	color;
}	t_pixel;

typedef struct s_bresvars {
	t_pixel	start;
	t_pixel	end;
	t_pixel delta;
	int		step[2];
	int		error[2];
	int		len;
	int		remain;
}	t_bresvars;

typedef struct s_props {
	float	scale;
	float	scale_z;
	float	angle[3];
	float	translate[3];
	int		canvas[4];
	bool	iso;
	bool	sphere;
	bool	box;
	uint8_t	view;
}	t_props;

typedef struct s_map {
	t_vec3f	*points;
	t_vec3f	*morph;
	t_vec3f	*polar;
	t_vec3f	*edges;
	t_vec3f	*corner[3];
	int		*z_storage;
	t_coord	*ang_coord;
	float	radius;
	int		sum_points;
	char	filename[32];
	int		height;
	int		width;
	char	*rows[ROW_MAX];
	bool	hex;
	float	limits[6];
	float	limits_sp[6];
	int		factor;
	int		pattern[4];
	int		skip;
	t_mat4	mat;
	t_props	props;
	bool	rainbow;
	uint8_t	menu;
	int		menu_width;
}	t_map;

typedef void	(*t_calc_ft)(t_vec3f *, t_vec3f *, t_mat4, t_map *);

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		bytes;
	uint64_t	created_at;
}	t_img;

typedef void	(*t_draw_ft)(t_img *, t_map *);

typedef struct s_mouse {
	bool	left;
	bool	right;
	int		last_left[2];
	int		last_right[2];
}	t_mouse;

typedef struct s_data {
	void	*mlx;
	void	*win;
	int		screen[2];
	t_img	*images;
	t_img	*render[2];
	t_img	*menu[3];
	t_map	map;
	t_mouse	mouse;
	t_calc_ft	calc_ft;
	t_draw_ft	draw_ft;
}	t_data;

void	ft_set_ft_ptr(t_data *data, int choose);

//check.c
void	ft_check_map(t_map *map, char *filename);
void	ft_check_filename(t_map *map, char *filename);
void	ft_extract_rows(t_map *map, int fd);
bool	ft_check_row(t_map *map, char *row);
int		ft_count_num_in_row(char *line, bool *hex);

//parse.c
void	ft_parse_map(t_map *map);
void	ft_map_alloc(t_map *map);
void	ft_parse_line(t_map *map, char *line, int index);
void	ft_set_colors(t_map *map, t_vec3f *points);

//draw.c
void	ft_put_pix_to_image(t_img *img, int x, int y, int color);
void	ft_draw_wirelines(t_img *img, t_map *map);
void	ft_connect_points(t_img *img, t_vec3f *morph_p, int line, t_map *map);
void	fill_background(t_img *img, int color, int size[2]);
void	ft_draw_points(t_img *img, t_map *map);

//color.c
int		ft_gradient(int color_start, int color_end, double len, double pos);
void	ft_set_pattern(int pattern[4], int choice);
void	ft_set_morph_color(t_vec3f *morph, t_vec3f *points, int sum);
void	ft_set_argb_values(t_color *color, uint8_t r, uint8_t g, uint8_t b);
uint32_t	ft_rainbow(double ratio);
void	ft_skittles(t_map *map, t_vec3f *morph);

//key_hooks.c
int		ft_key_hook_press(int key, t_data *data);
void	ft_key_hook_press2(int key, t_map *map);
void	ft_key_translate(int key, t_map *map);
void	ft_key_angle(int key, t_map *map);
void	ft_key_angle2(int key, t_map *map);
void	ft_key_zoom(int key, t_map *map);
//key_hooks2.c
void	ft_key_scale(int key, t_map *map);
void	ft_key_color(int key, t_map *map);
void	ft_key_sphere(int key, t_map *map);
void	ft_key_view(int key, t_map *map);
void	ft_key_stuff(int key, t_map *map, t_data *data);
//key_hooks3.c
void	ft_key_ftptr(int key, t_data *data);
void	ft_key_skip(int key, t_map *map);
void	ft_key_toggle_menu(t_data *data);
void	ft_key_toggle_controls(t_data *data);

//mouse.c
int		ft_mouse_hook_press(int button, int x, int y, t_data *data);
int		ft_mouse_hook_release(int button, int x, int y, t_data *data);
int		ft_mouse_hook_move(int x, int y, t_data *data);
void	ft_mouse_angle(int x, int y, t_data *data);
void	ft_mouse_translate(int x, int y, t_data *data);

//window.c
void	ft_init_window(t_data *data);
void	ft_init_image(t_data *data, t_img *img, int win_x, int win_y);
void	ft_start_mlx_loop(t_data *data);

//terminate.c
void	ft_terminate(char *message);
void	ft_free_rows(char *row, char *rows[ROW_MAX], int fd, int num);
void	ft_free_map_ptr(t_map *map, char *string);
void	ft_destroy_images(t_data *data);
void	ft_free_mlx(t_data *data, char *string, bool error);

//matrix.c
t_vec3f	ft_mult_vec3f_mat4(t_vec3f vec, t_mat4 mat);
void	ft_build_transmat(t_mat4 mat, t_props props);
void	ft_init_mat4(t_mat4 matrix);
void	ft_copy_mat4(const t_mat4 src, t_mat4 dest);
void	ft_mult_mat4(const t_mat4 first, const t_mat4 second, t_mat4 result);

//rotation.c
void	ft_rotate_x(t_mat4 trans, float roll);
void	ft_rotate_y(t_mat4 trans, float pitch);
void	ft_rotate_z(t_mat4 trans, float yaw);

//reshape.c
void	ft_init_project(t_data *data);
void	ft_scale_z(t_vec3f *points, int *z_storage, int sum, float scale_z);
void	ft_calc_morph(t_vec3f *morph, t_vec3f *points, t_mat4 mat, t_map *map);
int		ft_render(t_data *data);

//map_utils.c
void	ft_map_init(t_map *map);
void	ft_set_limits_xy(t_map *map);
void	ft_find_limits_z(t_map *map);
void	ft_fill_z_storage(t_map *map);
void	ft_set_canvas_size(int canvas[4], int x, int y);

//utils.c
int		ft_move_atoi(char *line);
int		ft_jump_over_hex(char *line);
int		ft_hex_to_dec(char *line, int len);
int		ft_wrap_angle(float angle, int factor);
void	ft_set_view_angle(float angle[3], uint8_t index);

//swap.c
void	ft_swap_img_ptr(t_img **a, t_img **b);
void	ft_swap_points(t_vec3f *start, t_vec3f *end);

//menu.c
void	ft_init_menu(t_data *data);
void	ft_write_menu(t_data *data);

//print_utils.c
void	ft_print_mat4(t_mat4 matrix);
void	ft_print_point(t_vec3f point);

//box.c
void	ft_set_corners(t_vec3f *corner, float limits[6]);
int		ft_is_outside(t_vec3f point, int canvas[2], float padding);
float	ft_fit_box(t_vec3f *corner, t_mat4 mat, t_props props);
void	ft_draw_box(t_img *img, t_vec3f *corner, int size[2]);

//precalc_matrix.c
void	ft_precalc_rot_x(t_mat4 mat, int index);
void	ft_precalc_rot_y(t_mat4 mat, int index);
void	ft_precalc_rot_z(t_mat4 mat, int index);
//precalc_matrix2.c
void	ft_precalc_zoom(t_mat4 mat, int index);
void	ft_precalc_view(t_mat4 mat, int index);

//shapes.c
void	ft_draw_circle(t_img *img, t_pixel center, int radius);

//sphere.c
void	ft_set_ang_coords(t_map *map, int sum);
void	ft_find_limits_sphere(t_map *map, t_vec3f *polar);
void	ft_calc_sphere_points(t_map *map, t_coord *ang_coord, t_vec3f *polar);

//time.c
uint64_t	ft_get_timeofday_ms(void);
uint64_t	ft_timestamp_ms(t_img *img);

//bresenham.c
void	ft_prep_draw_line(t_img *img, t_vec3f start, t_vec3f end, int size[2]);
int		ft_init_bresvars(t_bresvars *vars, t_vec3f start, t_vec3f end);
void	ft_draw_line(t_img *img, t_bresvars *vars);

//clipping.c
//can be included in bresenham
void	ft_clip_line(t_vec3f *start, t_vec3f *end, int size[2]);
void	ft_clip_coord_x(t_vec3f *start, t_vec3f *end, int size[2]);
void	ft_clip_coord_y(t_vec3f *start, t_vec3f *end, int size[2]);

//wobble.c
void	ft_wobble(t_vec3f *morph, t_vec3f *points, t_mat4 mat, t_map *map);

//numconvert.c
void	ft_ftoa_in_place(float num, char *str, int precision);
void	ft_itoa_in_place(int num, char *str);


//test.c
void	test(t_data *data);

#endif
