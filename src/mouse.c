/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 08:30:19 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/05 21:18:06 by gwolf            ###   ########.fr       */
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
	else if (button == M_RIGHT)
	{
		data->mouse.right = true;
		data->mouse.last_right[X] = x;
		data->mouse.last_right[Y] = y;
	}
	else if (button == M_SCROLL_UP)
	{
		data->map.props.scale += data->map.factor * 0.1;
		ft_precalc_zoom_in(data->map.mat, data->map.factor * 0.5);
	}
	else if (button == M_SCROLL_DOWN)
	{
		data->map.props.scale -= data->map.factor * 0.1;
		ft_precalc_zoom_out(data->map.mat, data->map.factor * 0.5);
	}
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
		ft_mouse_angle(x, y, data);
	}
	if (data->mouse.right)
	{
		ft_mouse_translate(x, y, data);
	}
	ft_redraw(data);
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
	data->map.props.angle[X] += delta_x;
	data->map.props.angle[Y] -= delta_y;
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
	data->map.props.translate[Y] -= delta_y;
	data->mouse.last_right[X] = x;
	data->mouse.last_right[Y] = y;
	data->map.mat[3][0] -= delta_x;
	data->map.mat[3][1] -= delta_y;
}
