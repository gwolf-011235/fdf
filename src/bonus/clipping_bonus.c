/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:02:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/22 09:32:02 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_clip_line(t_vec3f *start, t_vec3f *end, int size[2])
{
	if (end->x < 0 || end->x > size[X])
	{
		ft_clip_coord_x(start, end, size);
	}
	if (end->y < 0 || end->y > size[Y])
	{
		ft_clip_coord_y(start, end, size);
	}
}

void	ft_clip_coord_x(t_vec3f *start, t_vec3f *end, int size[2])
{
	float	move;

	if (end->x < 0)
	{
		move = (0 - start->x) / (end->x - start->x);
		end->x = 0;
	}
	else
	{
		move = (size[X] - start->x) / (end->x - start->x);
		end->x = size[X] - 1;
	}
	end->y = start->y + move * (end->y - start->y);
}

void	ft_clip_coord_y(t_vec3f *start, t_vec3f *end, int size[2])
{
	float	move;

	if (end->y < 0)
	{
		move = (0 - start->y) / (end->y - start->y);
		end->y = 0;
	}
	else
	{
		move = (size[Y] - start->y) / (end->y - start->y);
		end->y = size[Y] - 1;
	}
	end->x = start->x + move * (end->x - start->x);
}
