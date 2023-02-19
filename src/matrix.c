/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:48:55 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/18 23:29:57 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

t_vec3f	ft_mult_vec3f_mat4(t_vec3f vec, t_mat4 mat)
{
	t_vec3f	result;

	result.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0] + mat[3][0];
	result.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1] + mat[3][1];
	result.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2] + mat[3][2];
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
}

void	ft_build_transmat(t_mat4 mat, t_props props)
{
	ft_init_mat4(mat);
	mat[0][0] = props.scale;
	mat[1][1] = props.scale;
	mat[2][2] = props.scale;
	mat[3][3] = 1;
	ft_rotate_x(mat, props.angle[X]);
	ft_rotate_y(mat, props.angle[Y]);
	ft_rotate_z(mat, props.angle[Z]);
	mat[3][0] = props.translate[X] + props.canvas[OFFSET_X];
	mat[3][1] = props.translate[Y] + props.canvas[OFFSET_Y];
	mat[3][2] = props.translate[Z];
}

void	ft_copy_mat4(const t_mat4 src, t_mat4 dest)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dest[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

void	ft_augment_mat4(t_mat4 mat, float augment[4][8])
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			augment[i][j] = mat[i][j];
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				augment[i][j + 4] = 1;
			else
				augment[i][j + 4] = 0;
			j++;
		}
		i++;
	}
}

void	ft_inverse_mat4(t_mat4 mat)
{
	int	i;
	int	j;
	int	k;
	float	ratio;
	float	temp[4][8];

	ft_augment_mat4(mat, temp);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i != j)
			{
				ratio = temp[j][i] / temp[i][i];
				k = 0;
				while (k < 2 * 4)
				{
					temp[j][k] = temp[j][k] - ratio * temp[i][k];
					k++;
				}
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 4;
		while (j < 2 * 4)
		{
			temp[i][j] = temp[i][j] / temp[i][i];
			j++;
		}
		i++;
	}
	ft_print_inverse(temp);
}


void	ft_mult_mat4(const t_mat4 first, const t_mat4 second, t_mat4 result)
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
