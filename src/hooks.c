/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:16:59 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/01 11:21:07 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int key_hook(int keycode, t_data *data)
{
	ft_key_props(keycode, data);
	ft_key_color(keycode, data);
	if (keycode == KEY_ESC)
	{
		ft_free_mlx(data, CYA, false);
		exit(0);
	}
	ft_redraw(data);
	printf("This is keycode: %d\n", keycode);
	return (0);
}

int	ft_wrap_angle(float angle, int factor)
{
	angle += factor;
	if (angle < 0)
		angle = 360 - factor;
	if (angle > 360)
		angle = 0 + factor;
	return (angle);
}

void	ft_key_props(int keycode, t_data *data)
{
	int	factor;

	factor = data->map.factor;
	if (keycode == KEY_A)
		data->map.props.angle[X] -= factor;
	if (keycode == KEY_S)
		data->map.props.angle[X] += factor;
	if (keycode == KEY_D)
		data->map.props.angle[Y] -= factor;
	if (keycode == KEY_F)
		data->map.props.angle[Y] += factor;
	if (keycode == KEY_G)
		data->map.props.angle[Z] -= factor;
	if (keycode == KEY_H)
		data->map.props.angle[Z] += factor;
	if (keycode == KEY_Q)
		data->map.props.scale += factor;
	if (keycode == KEY_W)
		data->map.props.scale -= factor;
	if (keycode == KEY_ARROW_LEFT)
		data->map.props.translate[X] -= factor;
	if (keycode == KEY_ARROW_RIGHT)
		data->map.props.translate[X] += factor;
	if (keycode == KEY_ARROW_UP)
		data->map.props.translate[Y] -= factor;
	if (keycode == KEY_ARROW_DOWN)
		data->map.props.translate[Y] += factor;
}

void	ft_key_color(int keycode, t_data *data)
{
	if (keycode == KEY_ONE)
		ft_set_pattern(data->map.pattern, 0);
	if (keycode == KEY_TWO)
		ft_set_pattern(data->map.pattern, 1);
	if (keycode == KEY_THREE)
		ft_set_pattern(data->map.pattern, 2);
	if (keycode == KEY_FOUR)
		ft_set_pattern(data->map.pattern, 3);
	ft_set_colors(&data->map, data->map.points);
}
