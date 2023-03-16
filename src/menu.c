/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:38:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/16 02:01:25 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_menu(t_data *data)
{
	const static char	files[3][20] = {
		"assets/menu.xpm",
		"assets/controls.xpm",
		"assets/layer.xpm"};
	int	temp_x;
	int	temp_y;

	data->menu[0]->ptr = mlx_xpm_file_to_image(data->mlx, (char *)files[0], &temp_x, &temp_y);
	if (data->menu[0]->ptr == NULL)
		ft_free_mlx(data, (char *)files[0], true); 
	data->menu[1]->ptr = mlx_xpm_file_to_image(data->mlx, (char *)files[1], &temp_x, &temp_y);
	if (data->menu[1]->ptr == NULL)
		ft_free_mlx(data, (char *)files[1], true); 
	data->menu[2]->ptr = mlx_xpm_file_to_image(data->mlx, (char *)files[2], &temp_x, &temp_y);
	if (data->menu[2]->ptr == NULL)
		ft_free_mlx(data, (char *)files[2], true); 
	mlx_set_font(data->mlx, data->win,
		"-misc-fixed-medium-r-normal-*-15-*-*-100-*-*-iso8859-1");
}

void	ft_mlx_put_int(t_data *data, int pos[2], int num, int pad)
{
	int		numlen;
	char	str[8];

	if (num < 0)
		numlen = 1;
	else
		numlen = 0;
	numlen += ft_count_digit(num);
	if (numlen > 7)
	{
		mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, "max");
		return ;
	}
	ft_memset(str, 0, 8);
	pad -= numlen;
	if (pad > 0)
	{
		ft_itoa_in_place(num, str + pad);
		while (pad--)
			str[pad] = ' ';
	}
	else
		ft_itoa_in_place(num, str);
	mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, str);
}

void	ft_mlx_put_float(t_data *data, int pos[2], float num, int prec)
{
	int		numlen;
	char	str[8];
	int		padding;

	if (num < 0)
		numlen = 1;
	else
		numlen = 0;
	numlen += ft_count_digit(num);
	if (numlen > 3)
	{
		mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, "max");
		return ;
	}
	ft_memset(str, 0, 8);
	padding = 3 - numlen;
	ft_ftoa_in_place(num, str + padding, prec);
	while (padding--)
		str[padding] = ' ';
	mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, str);
}

void	ft_write_menu(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 30, 85, 0x0, "Name:");
	mlx_string_put(data->mlx, data->win, 90, 85, 0x0, data->map.filename);
	mlx_string_put(data->mlx, data->win, 30, 125, 0x0, "Rows (x):");
	ft_mlx_put_int(data, (t_pos){130, 125}, data->map.width, 3);
	mlx_string_put(data->mlx, data->win, 30, 145, 0x0, "Cols (y):");
	ft_mlx_put_int(data, (t_pos){130, 145}, data->map.height, 3);
	mlx_string_put(data->mlx, data->win, 30, 165, 0x0, "> Points:");
	ft_mlx_put_int(data, (t_pos){130, 165}, data->map.sum_points, 3);
	mlx_string_put(data->mlx, data->win, 30, 205, 0x0, "Hex-Colors:");
	if (data->map.hex)
		mlx_string_put(data->mlx, data->win, 150, 205, 0x00FF00, "found");
	else
		mlx_string_put(data->mlx, data->win, 150, 205, 0x0, "no");
	mlx_string_put(data->mlx, data->win, 110, 315, 0x0, "yaw   (x):");
	mlx_string_put(data->mlx, data->win, 110, 340, 0x0, "pitch (y):");
	mlx_string_put(data->mlx, data->win, 110, 365, 0x0, "roll  (z):");
	mlx_string_put(data->mlx, data->win, 110, 430, 0x0, "zoom:");
	mlx_string_put(data->mlx, data->win, 110, 510, 0x0, "z-scale:");
	mlx_string_put(data->mlx, data->win, 110, 590, 0x0, "mod-level:");
	mlx_string_put(data->mlx, data->win, 110, 655, 0x0, "          x:");
	mlx_string_put(data->mlx, data->win, 110, 670, 0x0, "translate");
	mlx_string_put(data->mlx, data->win, 110, 685, 0x0, "          y:");
	mlx_string_put(data->mlx, data->win, 110, 770, 0x0, "sampling:");
}

void	ft_mlx_put_viewname(t_data *data, uint8_t index, int pos[2])
{
	char	str[5];
	static const char views[5][5] = {
		"None", "Iso", "Top", "Side", "Nice"};

	ft_memset(str, 0, 5);
	ft_strlcpy(str, views[index], 5);
	mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, str);
}

void	ft_mlx_put_colorscheme(t_data *data, uint8_t index, int pos[2])
{
	char	str[7];
	static const char colorscheme[5][7] = {
		"Init", "B & W", "Ruppi", "Matrix", "Pop"};

	ft_memset(str, 0, 7);
	ft_strlcpy(str, colorscheme[index], 7);
	mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, str);
}

void	ft_update_menu(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->menu[2]->ptr, 220, 280);
	ft_mlx_put_int(data, (t_pos){250, 315}, data->map.props.angle[X], 3);
	ft_mlx_put_int(data, (t_pos){250, 340}, data->map.props.angle[Y], 3);
	ft_mlx_put_int(data, (t_pos){250, 365}, data->map.props.angle[Z], 3);
	if (data->map.props.scale >= 1000)
		mlx_string_put(data->mlx, data->win, 240, 430, RED, "MAX");
	else if (data->map.props.scale < 0.1)
		mlx_string_put(data->mlx, data->win, 240, 430, RED, "MIN");
	else
		ft_mlx_put_float(data, (t_pos){220, 430}, data->map.props.scale, 2);
	if (data->map.props.scale_z >= 10.0)
		mlx_string_put(data->mlx, data->win, 240, 510, RED, "MAX");
	else if (data->map.props.scale_z <= -10.0)
		mlx_string_put(data->mlx, data->win, 240, 510, RED, "MIN");
	else
		ft_mlx_put_float(data, (t_pos){220, 510}, data->map.props.scale_z, 2);
	if (data->map.factor == 1)
		mlx_string_put(data->mlx, data->win, 240, 590, GREEN, "min");
	else if (data->map.factor == 3)
		mlx_string_put(data->mlx, data->win, 240, 590, YELLOW, "Mid");
	else 
		mlx_string_put(data->mlx, data->win, 240, 590, RED, "MAX");
	ft_mlx_put_int(data, (t_pos){210, 655}, data->map.props.translate[X], 7);
	ft_mlx_put_int(data, (t_pos){210, 685}, data->map.props.translate[Y], 7);
	mlx_string_put(data->mlx, data->win, 245, 100, 0x0, "1:");
	ft_mlx_put_int(data, (t_pos){250, 100}, data->map.skip, 3);
	ft_mlx_put_viewname(data, data->map.props.view, (t_pos){220, 120});
	ft_mlx_put_colorscheme(data, data->map.pattern[4], (t_pos){220, 140});
	ft_mlx_put_int(data, (t_pos){220, 160}, 1000 / data->fps, 3);

}
