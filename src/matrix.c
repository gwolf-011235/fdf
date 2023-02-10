/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:48:55 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/10 13:28:33 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void	rotate(t_vec3f *point, double ang_x, double ang_y, double ang_z)
{
	if (ang_x)
	{
		ang_x = ang_x / 57.29578;
		point->x = 1 * point->x + 0 * point->y + 0 * point->z;
		point->y = 0 * point->x + cos(ang_x) * point->y + -sin(ang_x) * point->z;
		point->z = 0 * point->x + sin(ang_x) * point->y + cos(ang_x) * point->z;
	}
	if (ang_y)
	{
		ang_y = ang_y / 57.29578;
		point->x = cos(ang_y) * point->x + 0 * point->y + sin(ang_y) * point->z;
		point->y = 0 * point->x + 1 * point->y + 0 * point->z;
		point->z = -sin(ang_y) * point->x + 0 * point->y + cos(ang_y) * point->z;
	}
	if (ang_z)
	{
		ang_z = ang_z / 57.29578;
		point->x = cos(ang_z) * point->x + -sin(ang_z) * point->y + 0 * point->z;
		point->y = sin(ang_z) * point->x + cos(ang_z) * point->y + 0 * point->z;
		point->z = 0 * point->x + 0 * point->y + 1 * point->z;
	}
}

t_vec3f	ft_mult_vec3f_mat4(t_vec3f vec, t_mat4 mat)
{
	t_vec3f	result;

	result.x = mat[0][0] * vec.x + mat[0][1] * vec.y + mat[0][2] * vec.z + mat[0][3];
	result.y = mat[1][0] * vec.x + mat[1][1] * vec.y + mat[1][2] * vec.z + mat[1][3];
	result.z = mat[2][0] * vec.x + mat[2][1] * vec.y + mat[2][2] * vec.z + mat[2][3];
	return (result);
}

void	ft_init_mat4(t_mat4 matrix)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[2][2] = 1;
	matrix[3][3] = 1;
}

void	ft_copy_mat4(t_mat4 orig, t_mat4 copy)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			copy[i][j] = orig[i][j];
			j++;
		}
		i++;
	}

}

void	ft_mult_mat4(t_mat4 first, t_mat4 second, t_mat4 result)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				result[i][j] += first[i][k] * second[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}

void	fill_mat4(t_mat4 matrix, t_vec3f *points)
{
	int i;

	i = 0;
	while (i < 4)
	{
		matrix[i][0] = points[i].x;
		matrix[i][1] = points[i].y;
		matrix[i][2] = points[i].z;
		i++;
	}
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}

void	lookat(t_vec3f from, t_vec3f to, t_vec3f up, t_mat4 cam2world)
{
	t_vec3f	forward;
	t_vec3f	right;
	t_vec3f	newup;
	t_vec3f points[4];

	forward = vec3_subtract(from, to);
	vec3_normalize(&forward);
	right = vec3_cross(up, forward);
	vec3_normalize(&right);
	newup = vec3_cross(forward, right);

	points[0] = right;
	points[1] = newup;
	points[2] = forward;
	points[3] = from;
	fill_mat4(cam2world, points);
}
