/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:55:29 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 11:58:01 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_canvas_size(int canvas[4], int x, int y)
{
	if (x)
	{
		if (canvas[X] == 0)
			canvas[X] = x;
		else
			canvas[X] += x;
		canvas[OFFSET_X] = canvas[X] / 2;
	}
	if (y)
	{
		if (canvas[Y] == 0)
			canvas[Y] = y;
		else
			canvas[Y] += y;
		canvas[OFFSET_Y] = canvas[Y] / 2;
	}
}

void	ft_set_ft_ptr(t_data *data, uint8_t index)
{
	static const t_calc_ft	calc_ptr[2] = {ft_calc_morph, ft_wobble};
	static const t_draw_ft	draw_ptr[2] = {ft_draw_wirelines, ft_draw_points};

	if (index == 0)
		data->calc_ft = calc_ptr[0];
	else if (index == 1)
		data->calc_ft = calc_ptr[1];
	else if (index == 2)
		data->draw_ft = draw_ptr[0];
	else if (index == 3)
		data->draw_ft = draw_ptr[1];
}

void	ft_set_view_angles(float angle[3], uint8_t index)
{
	static const float	view_angle[5][3] = {
	{0}, {35, 0, 45}, {0, 0, 0}, {0, 90, 0}, {54, 0, 45}};

	angle[X] = view_angle[index][X];
	angle[Y] = view_angle[index][Y];
	angle[Z] = view_angle[index][Z];
}
