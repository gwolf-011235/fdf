/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:38:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/12 23:06:07 by gwolf            ###   ########.fr       */
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

void	ft_write_menu(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 30, 85, 0x0, data->map.filename);
	mlx_string_put(data->mlx, data->win, 30, 125, 0x0, "Points: 25000");
	mlx_string_put(data->mlx, data->win, 30, 165, 0x0, "x: 9 | y: 11");
	if (data->map.hex)
		mlx_string_put(data->mlx, data->win, 30, 205, 0x0, "Hex-Colors: yes");
	else
		mlx_string_put(data->mlx, data->win, 30, 205, 0x0, "Hex-Colors: no");
	mlx_string_put(data->mlx, data->win, 150, 315, 0x0, "yaw (x):   360");
	mlx_string_put(data->mlx, data->win, 150, 340, 0x0, "pitch (y): 9");
	mlx_string_put(data->mlx, data->win, 150, 365, 0x0, "roll (z):  9");


}
