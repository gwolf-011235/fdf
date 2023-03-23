/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalc_matrix1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 07:58:40 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 17:36:20 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_precalc_rot_x(t_mat4 mat, int index)
{
	static const t_mat4	rot_x[6] = {
	{{1, 0, 0, 0}, {0, COS_1, SIN_1, 0},
	{0, -SIN_1, COS_1, 0}, {0, 0, 0, 1}
	},
	{{1, 0, 0, 0}, {0, COS_1, -SIN_1, 0},
	{0, SIN_1, COS_1, 0}, {0, 0, 0, 1}
	},
	{{1, 0, 0, 0}, {0, COS_3, SIN_3, 0},
	{0, -SIN_3, COS_3, 0}, {0, 0, 0, 1}
	},
	{{1, 0, 0, 0}, {0, COS_3, -SIN_3, 0},
	{0, SIN_3, COS_3, 0}, {0, 0, 0, 1}
	},
	{{1, 0, 0, 0}, {0, COS_5, SIN_5, 0},
	{0, -SIN_5, COS_5, 0}, {0, 0, 0, 1}
	},
	{{1, 0, 0, 0}, {0, COS_5, -SIN_5, 0},
	{0, SIN_5, COS_5, 0}, {0, 0, 0, 1}}};
	t_mat4				temp;

	ft_init_mat4(temp);
	ft_mult_mat4(rot_x[index], mat, temp);
	ft_copy_mat4(temp, mat);
}

void	ft_precalc_rot_y(t_mat4 mat, int index)
{
	static const t_mat4	rot_y[6] = {
	{{COS_1, 0, -SIN_1, 0}, {0, 1, 0, 0},
	{SIN_1, 0, COS_1, 0}, {0, 0, 0, 1}
	},
	{{COS_1, 0, SIN_1, 0}, {0, 1, 0, 0},
	{-SIN_1, 0, COS_1, 0}, {0, 0, 0, 1}
	},
	{{COS_3, 0, -SIN_3, 0}, {0, 1, 0, 0},
	{SIN_3, 0, COS_3, 0}, {0, 0, 0, 1}
	},
	{{COS_3, 0, SIN_3, 0}, {0, 1, 0, 0},
	{-SIN_3, 0, COS_3, 0}, {0, 0, 0, 1}
	},
	{{COS_5, 0, -SIN_5, 0}, {0, 1, 0, 0},
	{SIN_5, 0, COS_5, 0}, {0, 0, 0, 1}
	},
	{{COS_5, 0, SIN_5, 0}, {0, 1, 0, 0},
	{-SIN_5, 0, COS_5, 0}, {0, 0, 0, 1}}};
	t_mat4				temp;

	ft_init_mat4(temp);
	ft_mult_mat4(rot_y[index], mat, temp);
	ft_copy_mat4(temp, mat);
}

void	ft_precalc_rot_z(t_mat4 mat, int index)
{
	static const t_mat4	rot_z[6] = {
	{{COS_1, SIN_1, 0, 0}, {-SIN_1, COS_1, 0, 0},
	{0, 0, 1, 0}, {0, 0, 0, 1}
	},
	{{COS_1, -SIN_1, 0, 0}, {SIN_1, COS_1, 0, 0},
	{0, 0, 1, 0}, {0, 0, 0, 1}
	},
	{{COS_3, SIN_3, 0, 0}, {-SIN_3, COS_3, 0, 0},
	{0, 0, 1, 0}, {0, 0, 0, 1}
	},
	{{COS_3, -SIN_3, 0, 0}, {SIN_3, COS_3, 0, 0},
	{0, 0, 1, 0}, {0, 0, 0, 1}
	},
	{{COS_5, SIN_5, 0, 0}, {-SIN_5, COS_5, 0, 0},
	{0, 0, 1, 0}, {0, 0, 0, 1}
	},
	{{COS_5, -SIN_5, 0, 0}, {SIN_5, COS_5, 0, 0},
	{0, 0, 1, 0}, {0, 0, 0, 1}}};
	t_mat4				temp;

	ft_init_mat4(temp);
	ft_mult_mat4(rot_z[index], mat, temp);
	ft_copy_mat4(temp, mat);
}
