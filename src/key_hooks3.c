/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:01 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/10 17:07:43 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_key_ftptr(int key, t_data *data)
{
	static bool	calc;
	static bool	draw;

	if (key == KEY_ENTER)
	{
		calc = !calc;
		if (calc)
			ft_set_ft_ptr(data, 1);
		else
			ft_set_ft_ptr(data, 0);
	}
	if (key == KEY_J)
	{
		draw = !draw;
		if (draw)
			ft_set_ft_ptr(data, 3);
		else
			ft_set_ft_ptr(data, 2);
	}
}

void	ft_key_skip(int key, t_map *map)
{
	if (key == KEY_K)
	{
		map->skip--;
		if (!map->skip)
			map->skip = 1;
	}
	if (key == KEY_L)
	{
		map->skip++;
		if (map->skip >= 10)
			map->skip = 10;
	}
}
