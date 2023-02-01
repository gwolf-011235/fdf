/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:48:55 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/27 19:04:46 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

t_point	rotate_x(t_point point, double angle)
{
	double	mat_x[3][3];

	mat_x[0][0] = 1;
	mat_x[0][1] = 0;
	mat_x[0][2] = 0;
	mat_x[1][0] = 0;
	mat_x[1][1] = cos(angle);
	mat_x[1][2] = -sin(angle);
	mat_x[2][0] = 0;
	mat_x[2][1] = sin(angle);
	mat_x[2][2] = cos(angle);
	return (matrix_point(mat_x, point));
}

t_point	rotate_y(t_point point, double angle)
{
	double	mat_y[3][3];

	mat_y[0][0] = cos(angle);
	mat_y[0][1] = 0;
	mat_y[0][2] = sin(angle);
	mat_y[1][0] = 0;
	mat_y[1][1] = 1;
	mat_y[1][2] = 0;
	mat_y[2][0] = -sin(angle);
	mat_y[2][1] = 0;
	mat_y[2][2] = cos(angle);
	return (matrix_point(mat_y, point));
}

t_point	rotate_z(t_point point, double angle)
{
	double	mat_z[3][3];

	mat_z[0][0] = cos(angle);
	mat_z[0][1] = -sin(angle);
	mat_z[0][2] = 0;
	mat_z[1][0] = sin(angle);
	mat_z[1][1] = cos(angle);
	mat_z[1][2] = 0;
	mat_z[2][0] = 0;
	mat_z[2][1] = 0;
	mat_z[2][2] = 1;
	return (matrix_point(mat_z, point));
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
