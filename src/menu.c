/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:38:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/19 20:57:38 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_write_map_info(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 30, 85, 0x0, "Name:");
	mlx_string_put(data->mlx, data->win, 90, 85, 0x0, data->map.filename);
	mlx_string_put(data->mlx, data->win, 30, 125, 0x0, "Rows (x):");
	ft_mlx_put_int(data, (t_pos){130, 125}, data->map.width, 3);
	mlx_string_put(data->mlx, data->win, 30, 145, 0x0, "Cols (y):");
	ft_mlx_put_int(data, (t_pos){130, 145}, data->map.height, 3);
	mlx_string_put(data->mlx, data->win, 30, 165, 0x0, "= Points:");
	ft_mlx_put_int(data, (t_pos){130, 165}, data->map.sum_points, 3);
	mlx_string_put(data->mlx, data->win, 30, 185, 0x0, "Hex-Colors:");
	if (data->map.hex)
		mlx_string_put(data->mlx, data->win, 150, 185, GREEN, "found");
	else
		mlx_string_put(data->mlx, data->win, 150, 185, 0x0, "no");
}

void	ft_write_projection_info(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 100, 285, 0x0, "yaw   (x):");
	mlx_string_put(data->mlx, data->win, 100, 310, 0x0, "pitch (y):");
	mlx_string_put(data->mlx, data->win, 100, 335, 0x0, "roll  (z):");
	mlx_string_put(data->mlx, data->win, 100, 390, 0x0, "zoom:");
	mlx_string_put(data->mlx, data->win, 100, 465, 0x0, "z-scale:");
	mlx_string_put(data->mlx, data->win, 100, 535, 0x0, "mod-level:");
	mlx_string_put(data->mlx, data->win, 100, 595, 0x0, "          x:");
	mlx_string_put(data->mlx, data->win, 100, 605, 0x0, "translate");
	mlx_string_put(data->mlx, data->win, 100, 620, 0x0, "          y:");
	mlx_string_put(data->mlx, data->win, 100, 680, 0x0, "sampling:");
	mlx_string_put(data->mlx, data->win, 100, 750, 0x0, "design:");
	mlx_string_put(data->mlx, data->win, 100, 815, 0x0, "view:");
	mlx_string_put(data->mlx, data->win, 100, 865, 0x0, "FPS:");
	mlx_string_put(data->mlx, data->win, 100, 890, 0x0, "Target:");
}

void	ft_write_menu(t_data *data)
{
	ft_write_map_info(data);
	ft_write_projection_info(data);
}

void	ft_update_menu(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->menu[2]->ptr, 210, 260);
	ft_mlx_put_int(data, (t_pos){230, 285}, data->map.props.angle[X], 3);
	ft_mlx_put_int(data, (t_pos){230, 310}, data->map.props.angle[Y], 3);
	ft_mlx_put_int(data, (t_pos){230, 335}, data->map.props.angle[Z], 3);
	if (data->map.props.scale >= 1000)
		mlx_string_put(data->mlx, data->win, 230, 390, RED, "MAX");
	else if (data->map.props.scale < 0.1)
		mlx_string_put(data->mlx, data->win, 230, 390, RED, "MIN");
	else
		ft_mlx_put_float(data, (t_pos){210, 390}, data->map.props.scale, 2);
	if (data->map.props.scale_z >= 10.0)
		mlx_string_put(data->mlx, data->win, 230, 465, RED, "MAX");
	else if (data->map.props.scale_z <= -10.0)
		mlx_string_put(data->mlx, data->win, 230, 465, RED, "MIN");
	else
		ft_mlx_put_float(data, (t_pos){210, 465}, data->map.props.scale_z, 2);
	if (data->map.factor == 1)
		mlx_string_put(data->mlx, data->win, 230, 535, GREEN, "min");
	else if (data->map.factor == 3)
		mlx_string_put(data->mlx, data->win, 230, 535, YELLOW, "Mid");
	else
		mlx_string_put(data->mlx, data->win, 230, 535, RED, "MAX");
	ft_update_menu2(data, &data->map);
}

void	ft_update_menu2(t_data *data, t_map *map)
{
	if (map->props.translate[X] >= 5000)
		mlx_string_put(data->mlx, data->win, 230, 595, RED, "MAX");
	else if (map->props.scale_z <= -5000)
		mlx_string_put(data->mlx, data->win, 230, 595, RED, "MIN");
	else
		ft_mlx_put_int(data, (t_pos){195, 595}, map->props.translate[X], 7);
	if (map->props.translate[Y] >= 5000)
		mlx_string_put(data->mlx, data->win, 230, 620, RED, "MAX");
	else if (map->props.scale_z <= -5000)
		mlx_string_put(data->mlx, data->win, 230, 620, RED, "MIN");
	else
		ft_mlx_put_int(data, (t_pos){195, 620}, map->props.translate[Y], 7);
	mlx_string_put(data->mlx, data->win, 210, 680, 0x0, "1:");
	ft_mlx_put_int(data, (t_pos){213, 680}, map->skip, 3);
	ft_mlx_put_colorscheme(data, map->pattern[4], (t_pos){210, 750});
	ft_mlx_put_viewname(data, map->props.view, (t_pos){210, 815});
	ft_mlx_put_int(data, (t_pos){210, 865}, 1000 / data->fps, 3);
	ft_mlx_put_int(data, (t_pos){210, 890}, FPS_TARGET, 3);
}
