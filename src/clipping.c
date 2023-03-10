/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:02:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/10 11:57:38 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_clip_line(t_vec3f *start, t_vec3f *end, int size[2], t_img *img)
{
	ft_clip_coord_x(start, end, size);
	ft_clip_coord_y(start, end, size);
}

void	ft_clip_coord_x(t_vec3f *start, t_vec3f *end, int size[2])
{
	float	move;

	if (end->x < 0 || end->x > size[X])
	{
		if (end->x < 0)
			move = (0 - start->x) / (end->x - start->x);
		if (end->x > size[X])
			move = (size[X] - start->x) / (end->x - start->x);
		end->y = start->y + move * (end->y - start->y);
		if (end->x > size[X])
			end->x = size[X];
		if (end->x < 0)
			end->x = 0;
	}
}

void	ft_clip_coord_y(t_vec3f *start, t_vec3f *end, int size[2])
{
	float	move;

	if (end->y < 0 || end->y > size[Y])
	{
		if (end->y < 0)
			move = (0 - start->y) / (end->y - start->y);
		if (end->y > size[Y])
			move = (size[Y] - start->y) / (end->y - start->y);
		end->x = start->x + move * (end->x - start->x);
		if (end->y > size[Y])
			end->y = size[Y];
		if (end->y < 0)
			end->y = 0;
	}
}
