/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 19:27:31 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/10 10:49:50 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	vec3_normalize(t_vec3f *point)
{
	float	len;

	len = sqrt(point->x * point->x + point->y * point->y + point->z * point->z);
	point->x /= len;
	point->y /= len;
	point->z /= len;
}

t_vec3f	vec3_cross(t_vec3f a, t_vec3f b)
{
	t_vec3f	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
}

t_vec3f	vec3_subtract(t_vec3f a, t_vec3f b)
{
	t_vec3f	result;

	result = (t_vec3f){a.x - b.x, a.y - b.y, a.z - b.z};
	return (result);
}
