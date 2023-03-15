/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:38:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/15 17:50:11 by gwolf            ###   ########.fr       */
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
		"-misc-fixed-medium-r-normal-*-15-*-*-100-*-*-iso8859-1");
}

void	ft_mlx_put_int(t_data *data, int x, int y, int num)
{
	int		numlen;
	char	str[4];
	int		padding;

	numlen = ft_count_digit(num);
	if (numlen > 3)
	{
		mlx_string_put(data->mlx, data->win, x, y, 0x0, "max");
		return ;
	}
	ft_memset(str, 0, 4);
	padding = 3 - numlen;
	ft_itoa_in_place(num, str + padding);
	while (padding--)
		str[padding] = ' ';
	mlx_string_put(data->mlx, data->win, x, y, 0x0, str);
}

void	ft_mlx_put_float(t_data *data, int pos[2], float num, int prec)
{
	int		numlen;
	char	str[8];
	int		padding;

	numlen = ft_count_digit(num);
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
	mlx_string_put(data->mlx, data->win, 120, 315, 0x0, "yaw   (x):");
	mlx_string_put(data->mlx, data->win, 120, 340, 0x0, "pitch (y):");
	mlx_string_put(data->mlx, data->win, 120, 365, 0x0, "roll  (z):");
	mlx_string_put(data->mlx, data->win, 120, 415, 0x0, "zoom:");
	mlx_string_put(data->mlx, data->win, 120, 495, 0x0, "z-scale:");
	mlx_string_put(data->mlx, data->win, 120, 580, 0x0, "sampling:");
	mlx_string_put(data->mlx, data->win, 120, 665, 0x0, "change:");
}

void	ft_mlx_put_viewname(t_data *data, uint8_t index)
{
	char	str[5];
	static const char views[5][5] = {
		"None", "Iso", "Top", "Side", "Nice"};

	ft_memset(str, 0, 5);
	ft_strlcpy(str, views[index], 5);
	mlx_string_put(data->mlx, data->win, 260, 400, 0x0, str);
}

void	ft_update_menu(t_data *data)
{
	ft_mlx_put_int(data, 260, 315, data->map.props.angle[X]);
	ft_mlx_put_int(data, 260, 340, data->map.props.angle[Y]);
	ft_mlx_put_int(data, 260, 365, data->map.props.angle[Z]);
	ft_mlx_put_float(data, (int[]){235, 415}, data->map.props.scale, 2);
	ft_mlx_put_float(data, (int[]){235, 495}, data->map.props.scale_z, 2);
	mlx_string_put(data->mlx, data->win, 255, 580, 0x0, "1:");
	ft_mlx_put_int(data, 258, 580, data->map.skip);
	if (data->map.factor == 1)
		mlx_string_put(data->mlx, data->win, 260, 665, 0x0, "min");
	else if (data->map.factor == 3)
		mlx_string_put(data->mlx, data->win, 260, 665, 0x0, "mid");
	else 
		mlx_string_put(data->mlx, data->win, 260, 665, 0x0, "max");
	ft_mlx_put_viewname(data, data->map.props.view);

}
