/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 08:30:19 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/01 10:37:31 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_mouse_press(int button, int x, int y, t_data *data)
{
	if (button == M_LEFT)
	{
		data->mouse.left = true;
		data->mouse.last_left[X] = x;
		data->mouse.last_left[Y] = y;
	}
	if (button == M_RIGHT)
	{
		data->mouse.right = true;
		data->mouse.last_right[X] = x;
		data->mouse.last_right[Y] = y;
	}
	if (button == M_SCROLL_UP)
		data->map.props.scale += 1;
	if (button == M_SCROLL_DOWN)
		data->map.props.scale -= 1;
	ft_redraw(data);
	return (0);
}

int	ft_mouse_release(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == M_LEFT)
		data->mouse.left = false;
	if (button == M_RIGHT)
		data->mouse.right = false;
	return (0);
}

int	ft_mouse_move(int x, int y, t_data *data)
{
	if (x > data->render.size[X] || x < 0 || y > data->render.size[Y] || y < 0)
		return (0);
	if (data->mouse.left)
	{
		data->map.props.angle[X] += data->mouse.last_left[Y] - y;
		data->map.props.angle[Y] -= data->mouse.last_left[X] - x;
		data->mouse.last_left[X] = x;
		data->mouse.last_left[Y] = y;
		ft_redraw(data);
	}
	if (data->mouse.right)
	{
		data->map.props.translate[X] -= data->mouse.last_right[X] - x;
		data->map.props.translate[Y] -= data->mouse.last_right[Y] - y;
		data->mouse.last_right[X] = x;
		data->mouse.last_right[Y] = y;
		ft_redraw(data);
	}
	return (0);
}
