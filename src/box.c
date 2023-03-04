/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:28:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/04 11:53:17 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_corner(t_vec3f *corner, int min[3], int max[3], int *z_store_c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (i == 1 || i == 2 || i == 5 || i == 6)
			corner[i].x = max[X];
		else
			corner[i].x = min[X];
		if (i == 2 || i == 3 || i == 6 || i == 7)
			corner[i].y = max[Y];
		else
			corner[i].y = min[Y];
		if (i < 4)
		{
			corner[i].z = min[Z];
			z_store_c[i] = min[Z];
		}
		else
		{
			corner[i].z = max[Z];
			z_store_c[i] = max[Z];
		}
		i++;
	}
}

float	ft_fit_box(t_vec3f *corner, t_mat4 mat, t_props props)
{
	int		i;
	t_vec3f	temp;

	props.scale = 0.01;
	while (1)
	{
		ft_build_transmat(mat, props);
		i = 0;
		while (i < 8)
		{
			temp = ft_mult_vec3f_mat4(corner[i], mat);
			if (ft_is_outside(temp, props.canvas, 0.1))
			{
				ft_printf("🔍 Scale\n   |%d|\n\n", (int)props.scale);
				return (props.scale);
			}
			i++;
		}
		props.scale += 0.010;
	}
}

void	ft_draw_box(t_img *img, t_vec3f *corner)
{
	t_vec3f	start;
	t_vec3f	end;
	int		i;

	i = 0;
	while (i < 4)
	{
		start = corner[i];
		end = corner[(i + 1) % 4];
		start.color = GREEN;
		end.color = GREEN;
		if (!start.hidden && !end.hidden)
			draw_line(img, start, end);
		end = corner[i + 4];
		start.color = BLUE;
		end.color = BLUE;
		if (!start.hidden && !end.hidden)
			draw_line(img, start, end);
		start = corner[i + 4];
		end = corner[((i + 1) % 4) + 4];
		start.color = RED;
		end.color = RED;
		if (!start.hidden && !end.hidden)
			draw_line(img, start, end);
		i++;
	}
}
