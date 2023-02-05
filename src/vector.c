/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 19:27:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/05 20:30:36 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	vec3_normalize(t_point *point)
{
	double len = sqrt(point->x * point->x + point->y * point->y + point->z * point->z);
	point->x /= len;
	point->y /= len;
	point->z /= len;
}

t_point	vec3_cross(t_point a, t_point b)
{
	t_point	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
}

t_point	vec3_subtract(t_point a, t_point b)
{
	t_point	result;

	result = (t_point){a.x - b.x, a.y - b.y, a.z - b.z};
	return (result);
}
