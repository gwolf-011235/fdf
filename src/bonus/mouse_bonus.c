/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 08:30:19 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/17 14:57:10 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_mouse_hook_press(int button, int x, int y, t_data *data)
{
	if (button == M_LEFT)
	{
		data->mouse.left = true;
		data->mouse.last_left[X] = x;
		data->mouse.last_left[Y] = y;
	}
	else if (button == M_RIGHT)
	{
		data->mouse.right = true;
		data->mouse.last_right[X] = x;
		data->mouse.last_right[Y] = y;
	}
	else if (button == M_SCROLL_UP && data->map.props.scale < 1000)
	{
		data->map.props.scale *= 1 + data->map.factor * 0.1;
		ft_precalc_zoom(data->map.mat, data->map.factor - 1);
	}
	else if (button == M_SCROLL_DOWN && data->map.props.scale > 0.1)
	{
		data->map.props.scale *= 1 - data->map.factor * 0.1;
		ft_precalc_zoom(data->map.mat, data->map.factor);
	}
	return (0);
}

int	ft_mouse_hook_release(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == M_LEFT)
		data->mouse.left = false;
	if (button == M_RIGHT)
		data->mouse.right = false;
	return (0);
}

int	ft_mouse_hook_move(int x, int y, t_data *data)
{
	if (x > data->screen[X] || x < 0
		|| y > data->screen[Y] || y < 0)
		return (0);
	if (data->mouse.left)
	{
		data->map.props.view = 0;
		ft_mouse_angle(x, y, data);
	}
	if (data->mouse.right)
	{
		ft_mouse_translate(x, y, data);
	}
	return (0);
}

void	ft_mouse_angle(int x, int y, t_data *data)
{
	int		delta_x;
	int		delta_y;
	float	distance;

	delta_x = data->mouse.last_left[Y] - y;
	delta_y = data->mouse.last_left[X] - x;
	distance = sqrt(delta_x * delta_x + delta_y * delta_y);
	if (distance < 5)
		return ;
	data->map.props.angle[X] = ft_wrap_angle(data->map.props.angle[X], delta_x);
	data->map.props.angle[Y] = ft_wrap_angle(data->map.props.angle[Y], delta_y);
	data->mouse.last_left[X] = x;
	data->mouse.last_left[Y] = y;
	ft_build_transmat(data->map.mat, data->map.props);
}

void	ft_mouse_translate(int x, int y, t_data *data)
{
	int		delta_x;
	int		delta_y;
	float	distance;

	delta_x = data->mouse.last_right[X] - x;
	delta_y = data->mouse.last_right[Y] - y;
	distance = sqrt(delta_x * delta_x + delta_y * delta_y);
	if (distance < 10)
		return ;
	data->map.props.translate[X] -= delta_x;
	if (data->map.props.translate[X] >= 5000
		|| data->map.props.translate[X] <= -5000)
		data->map.props.translate[X] += delta_x;
	else
		data->map.mat[3][0] -= delta_x;
	data->map.props.translate[Y] -= delta_y;
	if (data->map.props.translate[Y] >= 5000
		|| data->map.props.translate[Y] <= -5000)
		data->map.props.translate[Y] += delta_y;
	else
		data->map.mat[3][1] -= delta_y;
	data->mouse.last_right[X] = x;
	data->mouse.last_right[Y] = y;
}
