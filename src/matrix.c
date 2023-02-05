/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:48:55 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/05 19:29:20 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void	rotate(t_point *point, double ang_x, double ang_y, double ang_z)
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

void	project_2d(t_point *point)
{
	if (point->z == 0)
	{
		point->x = 0;
		point->y = 0;
	}
	else
	{
		point->x = point->x / -point->z;
		point->y = point->y / -point->z;
	}
	point->x = (point->x + WIN_X / 2) / WIN_X;
	point->y = (point->y + WIN_Y / 2) / WIN_Y;
	point->x = floor(point->x * WIN_X);
	point->y = floor((1 - point->y) * WIN_Y);
}

t_point	matrix_point(double mat[3][3], t_point point)
{
	t_point	rotate;

	rotate.x = mat[0][0] * point.x + mat[0][1] * point.y + mat[0][2] * point.z;
	rotate.y = mat[1][0] * point.x + mat[1][1] * point.y + mat[1][2] * point.z;
	rotate.z = mat[2][0] * point.x + mat[2][1] * point.y + mat[2][2] * point.z;
	return (rotate);
}

void	mat_mult(double first[3][3], double second[3][3], double mul[3][3])
{
	int		i;
	int		j;
	int		k;
	double	total;

	i = 0;
	total = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			k = 0;
			while (k < 3)
			{
				total += first[i][k] * second[k][j];
				k++;
			}
			mul[i][j] = total;
			total = 0;
			j++;
		}
		i++;
	}
}

void	fill_mat4(t_mat4 matrix, t_point *points)
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

void	lookat(t_point from, t_point to, t_point up, t_mat4 cam2world)
{
	t_point	forward;
	t_point	right;
	t_point	newup;
	t_point points[4];

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
