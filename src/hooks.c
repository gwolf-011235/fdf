/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:16:59 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/03 11:34:22 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ARROW_LEFT)
	{
		data->map.ang_x -= 3;
		ft_redraw(data);
	}
	if (keycode == KEY_ARROW_RIGHT)
	{
		data->map.ang_x += 3;
		ft_redraw(data);
	}
	if (keycode == KEY_ARROW_UP)
	{
		data->map.ang_y += 3;
		ft_redraw(data);
	}
	if (keycode == KEY_ARROW_DOWN)
	{
		data->map.ang_y -= 3;
		ft_redraw(data);
	}
	printf("This is keycode: %d\n", keycode);
	return (0);
}

int close_window(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	return (0);
}

int mouse_hook(int button, int x, int y, void *param)
{
	(void)param;
	printf("Mouse clicked!\nbutton: %d, x: %d, y: %d\n", button, x, y);
	return (0);
}

int mouse_move(int x, int y, void *param)
{
	(void)param;
	printf("Mouse moved!\nx: %d y: %d\n", x, y);
	return (0);
}

