/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:20:01 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/10 16:20:23 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_key_ftptr(int key, t_data *data)
{
	static bool	draw;
	static bool	calc;

	if (key == KEY_Z)
	{
		draw = !draw;
		if (draw)
			ft_set_ft_ptr(data, 1);
		else
			ft_set_ft_ptr(data, 0);
	}
	if (key == KEY_K)
	{
		calc = !calc;
		if (calc)
			ft_set_ft_ptr(data, 2);
		else
			ft_set_ft_ptr(data, 3);
	}
}
