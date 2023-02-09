/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:38:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/09 15:16:33 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_menu(t_data *data)
{
	int i;
	int j;

	data->menu.ptr = mlx_xpm_file_to_image(data->mlx, "image/menu.xpm", &i, &j);
	mlx_put_image_to_window(data->mlx, data->win, data->menu.ptr, 0, 0);
}
