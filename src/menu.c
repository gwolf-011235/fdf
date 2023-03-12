/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:38:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/10 21:56:47 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_menu(t_data *data)
{
	int	i;
	int	j;

	data->menu.ptr = mlx_xpm_file_to_image(data->mlx, "image/menu.xpm", &i, &j);
	mlx_set_font(data->mlx, data->win,
		"-misc-fixed-medium-r-normal-*-20-*-*-100-*-*-iso8859-1");
	//mlx_string_put(data->mlx, data->win, 120, 150, 0x0, "Hello, World!");
}
