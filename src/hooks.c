/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:16:59 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/24 15:12:03 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_A)
		data->map.props.angle[X] -= 1;
	if (keycode == KEY_S)
		data->map.props.angle[X] += 1;
	if (keycode == KEY_D)
		data->map.props.angle[Y] -= 3;
	if (keycode == KEY_F)
		data->map.props.angle[Y] += 3;
	if (keycode == KEY_G)
		data->map.props.angle[Z] -= 3;
	if (keycode == KEY_H)
		data->map.props.angle[Z] += 3;
	if (keycode == KEY_Q)
		data->map.props.scale += 1;
	if (keycode == KEY_W)
		data->map.props.scale -= 1;
	if (keycode == KEY_ARROW_LEFT)
		data->map.props.translate[X]--;
	if (keycode == KEY_ARROW_RIGHT)
		data->map.props.translate[X]++;
	if (keycode == KEY_ARROW_UP)
		data->map.props.translate[Y] -= 3;
	if (keycode == KEY_ARROW_DOWN)
		data->map.props.translate[Y] += 3;
	ft_redraw(data);
	printf("This is keycode: %d\n", keycode);
	return (0);
}

int close_window(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		ft_free_mlx(data, CYA, false);
		exit(0);
	}
	return (0);
}

int mouse_hook(int button, int x, int y, t_data *data)
{

	(void)data;
	printf("Mouse clicked!\nbutton: %d, x: %d, y: %d\n", button, x, y);
	(void)x;
	(void)y;
	(void)button;
	return (0);
}

int mouse_move(int x, int y, void *param)
{
	(void)param;
	printf("Mouse moved!\nx: %d y: %d\n", x, y);
	return (0);
}

