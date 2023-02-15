/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:38:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/13 07:17:11 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_menu(t_data *data)
{
	int i;
	int j;

	data->menu.ptr = mlx_xpm_file_to_image(data->mlx, "image/menu.xpm", &i, &j);
	mlx_set_font(data->mlx, data->win, "-misc-fixed-medium-r-normal--7-50-100-100-c-50-iso8859-1");
	mlx_string_put(data->mlx, data->win, 50, 50, 0x00FFFFFF, "Hello, World!");
	//mlx_put_image_to_window(data->mlx, data->win, data->menu.ptr, 0, 0);
}
