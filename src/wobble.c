/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wobble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:44:20 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/10 15:49:12 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_wobble(t_vec3f *morph, t_vec3f *points, t_mat4 mat, t_map *map)
{
	int		i;
	int		neg;

	i = 0;
	while (i < map->sum_points)
	{
		neg = 1;
		morph[i].x = points[i].x * mat[0][0] + points[i].y * mat[1][0]
			+ points[i].z * mat[2][0] + mat[3][0] + (rand() % (map->factor * 2)) * neg;
		morph[i].y = points[i].x * mat[0][1] + points[i].y * mat[1][1]
			+ points[i].z * mat[2][1] + mat[3][1] + (rand() % (map->factor * 2)) * neg;
		morph[i].z = points[i].x * mat[0][2] + points[i].y * mat[1][2]
			+ points[i].z * mat[2][2] + mat[3][2] + (rand() % (map->factor * 2)) * neg;
		if (morph[i].x < 0 || morph[i].x > map->props.canvas[X]
			|| morph[i].y < 0 || morph[i].y > map->props.canvas[Y])
			morph[i].hidden = true;
		else
			morph[i].hidden = false;
		i++;
	}
}
