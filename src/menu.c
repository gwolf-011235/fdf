/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:38:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/14 02:18:17 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_menu(t_data *data)
{
	int	temp_x;
	int	temp_y;

	data->menu[0]->ptr = mlx_xpm_file_to_image(data->mlx, "image/menu.xpm", &temp_x, &temp_y);
	data->menu[1]->ptr = mlx_xpm_file_to_image(data->mlx, "image/controls.xpm", &temp_x, &temp_y);
	mlx_set_font(data->mlx, data->win,
		"-misc-fixed-medium-r-normal-*-20-*-*-100-*-*-iso8859-1");
}

void	ft_mlx_put_int(t_data *data, int x, int y, int num)
{
	char	str[20];

	ft_memset(str, 0, 20);
	ft_itoa_in_place(num, str);
	mlx_string_put(data->mlx, data->win, x, y, 0x0, str);
}

void	ft_write_menu(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 30, 85, 0x0, "Name:");
	mlx_string_put(data->mlx, data->win, 90, 85, 0x0, data->map.filename);
	mlx_string_put(data->mlx, data->win, 30, 125, 0x0, "Rows (x):");
	ft_mlx_put_int(data, 130, 125, data->map.width);
	mlx_string_put(data->mlx, data->win, 30, 145, 0x0, "Cols (y):");
	ft_mlx_put_int(data, 130, 145, data->map.height);
	mlx_string_put(data->mlx, data->win, 30, 165, 0x0, "> Points:");
	ft_mlx_put_int(data, 130, 165, data->map.sum_points);
	mlx_string_put(data->mlx, data->win, 30, 205, 0x0, "Hex-Colors:");
	if (data->map.hex)
		mlx_string_put(data->mlx, data->win, 150, 205, 0x00FF00, "found");
	else
		mlx_string_put(data->mlx, data->win, 150, 205, 0x0, "no");
	mlx_string_put(data->mlx, data->win, 130, 315, 0x0, "yaw (x):");
	ft_mlx_put_int(data, 220, 315, data->map.props.angle[X]);
	mlx_string_put(data->mlx, data->win, 130, 340, 0x0, "pitch (y): 9");
	mlx_string_put(data->mlx, data->win, 130, 365, 0x0, "roll (z):  9");


}
