/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:48:55 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 15:51:09 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

t_vec3f	ft_mult_vec3f_mat4(t_vec3f vec, t_mat4 mat)
{
	t_vec3f	result;

	result.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0]
		+ mat[3][0];
	result.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1]
		+ mat[3][1];
	result.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2]
		+ mat[3][2];
	return (result);
}

void	ft_build_transmat(t_mat4 mat, t_props props)
{
	ft_init_mat4(mat);
	mat[0][0] = props.scale;
	mat[1][1] = props.scale;
	mat[2][2] = props.scale;
	mat[3][3] = 1;
	ft_precalc_view(mat, props.view);
	mat[3][0] = props.canvas[OFFSET_X];
	mat[3][1] = props.canvas[OFFSET_Y];
}

void	ft_init_mat4(t_mat4 mat)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	ft_copy_mat4(const t_mat4 src, t_mat4 dest)
{
	int	i;
	int	j;

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
