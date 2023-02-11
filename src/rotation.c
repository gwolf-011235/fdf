/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:26:37 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/11 08:39:35 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate_x(t_mat4 trans, float roll)
{
	t_mat4	rot_x;
	t_mat4	temp;
	float	roll_sin;
	float	roll_cos;

	roll_sin = sin(roll * RAD);
	roll_cos = cos(roll * RAD);
	ft_init_mat4(temp);
	ft_init_mat4(rot_x);
	rot_x[0][0] = 1;
	rot_x[1][1] = roll_cos;
	rot_x[1][2] = roll_sin;
	rot_x[2][1] = -roll_sin;
	rot_x[2][2] = roll_cos;
	rot_x[3][3] = 1;
	ft_mult_mat4(rot_x, trans, temp);
	ft_copy_mat4(temp, trans);
}

void	ft_rotate_y(t_mat4 trans, float pitch)
{
	t_mat4	rot_y;
	t_mat4	temp;
	float	pitch_sin;
	float	pitch_cos;

	pitch_sin = sin(pitch * RAD);
	pitch_cos = cos(pitch * RAD);
	ft_init_mat4(temp);
	ft_init_mat4(rot_y);
	rot_y[1][1] = 1;
	rot_y[0][0] = pitch_cos;
	rot_y[0][2] = -pitch_sin;
	rot_y[2][0] = pitch_sin;
	rot_y[2][2] = pitch_cos;
	rot_y[3][3] = 1;
	ft_mult_mat4(rot_y, trans, temp);
	ft_copy_mat4(temp, trans);
}

void	ft_rotate_z(t_mat4 trans, float yaw)
{
	t_mat4	rot_z;
	t_mat4	temp;
	float	yaw_sin;
	float	yaw_cos;

	yaw_sin = sin(yaw * RAD);
	yaw_cos = cos(yaw * RAD);
	ft_init_mat4(temp);
	ft_init_mat4(rot_z);
	rot_z[2][2] = 1;
	rot_z[0][0] = yaw_cos;
	rot_z[0][1] = yaw_sin;
	rot_z[1][0] = -yaw_sin;
	rot_z[1][1] = yaw_cos;
	rot_z[3][3] = 1;
	ft_mult_mat4(rot_z, trans, temp);
	ft_copy_mat4(temp, trans);
}

void	ft_static_rotate(t_mat4 trans, int rotate)
{
	const t_mat4 rot_x = {
		{1, 0, 0, 0},
		{0, 0.9998476951563913, 0.01745240643728351, 0},
		{0, -0.01745240643728351, 0.9998476951563913, 0},
		{0, 0, 0, 1}
	};

	if (rotate == 0)
	{
		ft_copy_mat4(rot_x, trans);
	}
}
