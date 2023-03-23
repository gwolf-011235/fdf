/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:26:06 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 17:01:13 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <math.h>

# include "mlx.h"
# include "ft_print.h"
# include "ft_fd.h"
# include "X.h"

# include "macro_general.h"
# include "macro_colors.h"
# include "err_message.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define RAD 0.01745329251

# define ROW_MAX 1000
# define KEY_ESC 65307 

typedef int		t_pos[2];

typedef float	t_mat4[4][4];

typedef struct s_color {
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_color;

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
	t_pixel	delta;
	int		step[2];
	int		error[2];
	int		len;
	int		remain;
}	t_bresvars;

typedef struct s_props {
	float	scale;
	int		canvas[4];
	uint8_t	view;
}	t_props;

typedef struct s_map {
	char		filename[22];
	int			width;
	int			height;
	int			sum_points;
	char		*rows[ROW_MAX];
	bool		hex;
	t_vec3f		*points;
	t_vec3f		*morph;
	t_vec3f		*corner[2];
	float		limits[6];
	int			sampling;
	int			pattern[5];
	t_mat4		mat;
	t_props		props;
}	t_map;

typedef void	(*t_calc_ft)(t_vec3f *, t_vec3f *, t_mat4, t_map *);

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		bytes;
}	t_img;

typedef void	(*t_draw_ft)(t_img *, t_map *);

typedef struct s_data {
	void		*mlx;
	void		*win;
	int			screen[2];
	t_img		render;
	t_map		map;
	t_calc_ft	calc_ft;
	t_draw_ft	draw_ft;
}	t_data;

//main.c

//check.c
void	ft_check_map(t_map *map, char *input);
void	ft_check_filename(char filename[22], char *input);
void	ft_extract_rows(t_map *map, int fd);
bool	ft_check_row(char *row, int width, int height, bool *hex);
int		ft_count_num_in_row(char *line, bool *hex);

//parse.c
void	ft_parse_map(t_map *map);
void	ft_map_alloc(t_map *map);
void	ft_parse_line(t_map *map, char *line, int index);

//draw.c
void	ft_put_pix_to_image(t_img *img, int x, int y, int color);
void	ft_draw_wirelines(t_img *img, t_map *map);
void	ft_connect_points(t_img *img, t_vec3f *morph_p, int line, t_map *map);

//color.c
void	ft_set_morph_color(t_vec3f *points, t_vec3f *morph, t_map *map);
int		ft_gradient(int color_start, int color_end, double len, double pos);
void	ft_set_pattern(int pattern[4], int choice);

//window.c
void	ft_init_window(t_data *data);
void	ft_init_image(t_data *data, t_img *img, int win_x, int win_y);
void	ft_start_mlx_loop(t_data *data);

//terminate.c
void	ft_terminate(char *message);
void	ft_free_rows(char *row, char *rows[ROW_MAX], int fd, int num);
void	ft_free_map_ptr(t_map *map, char *string);
void	ft_free_mlx(t_data *data, char *string, bool error);

//matrix.c
t_vec3f	ft_mult_vec3f_mat4(t_vec3f vec, t_mat4 mat);
void	ft_build_transmat(t_mat4 mat, t_props props);
void	ft_init_mat4(t_mat4 matrix);
void	ft_copy_mat4(const t_mat4 src, t_mat4 dest);
void	ft_mult_mat4(const t_mat4 first, const t_mat4 second, t_mat4 result);

//reshape.c
void	ft_init_projection(t_data *data);
void	ft_calc_morph(t_vec3f *morph, t_vec3f *points, t_mat4 mat, t_map *map);

//utils_limits.c
void	ft_set_limits_xy(t_map *map);
void	ft_find_limits_z(t_map *map);

//utils_set.c
void	ft_set_canvas_size(int canvas[4], int x, int y);
void	ft_set_ft_ptr(t_data *data, uint8_t index);

//utils.c
int		ft_move_atoi(char *line);
int		ft_jump_over_hex(char *line);
int		ft_hex_to_dec(char *line, int len);

//utils_prog.c
int		ft_close_program(t_data *data);
void	ft_init_data(t_data *data);

//box.c
void	ft_set_corners(t_vec3f *corner, float limits[6]);
int		ft_is_outside(t_vec3f point, int canvas[2], float padding);
float	ft_fit_box(t_vec3f *corner, t_mat4 mat, t_props props);

//precalc_matrix2.c
void	ft_precalc_zoom(t_mat4 mat, int index);
void	ft_precalc_view(t_mat4 mat, int index);

//bresenham.c
void	ft_prep_draw_line(t_img *img, t_vec3f start, t_vec3f end);
int		ft_init_bresvars(t_bresvars *vars, t_vec3f start, t_vec3f end);
void	ft_draw_line(t_img *img, t_bresvars *vars);

//key_hooks.c
int		ft_key_hook_press(int key, t_data *data);

#endif
