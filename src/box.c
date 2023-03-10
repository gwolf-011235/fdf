/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:28:13 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/10 13:06:08 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_corners(t_vec3f *corner, float limits[6])
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (i == 1 || i == 2 || i == 5 || i == 6)
			corner[i].x = limits[XMAX];
		else
			corner[i].x = limits[XMIN];
		if (i == 2 || i == 3 || i == 6 || i == 7)
			corner[i].y = limits[YMAX];
		else
			corner[i].y = limits[YMIN];
		if (i >= 4)
			corner[i].z = limits[ZMAX];
		else
			corner[i].z = limits[ZMIN];
		i++;
	}
}

int	ft_is_outside(t_vec3f point, int canvas[2], float padding)
{
	float	pad_x;
	float	pad_y;

	pad_x = canvas[X] * padding;
	pad_y = canvas[Y] * padding;
	if (point.x < (0 + pad_x) || point.x > (canvas[X] - pad_x))
		return (1);
	if (point.y < (0 + pad_y) || point.y > (canvas[Y] - pad_y))
		return (1);
	return (0);
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

	i = -1;
	while (++i < 4)
	{
		start = corner[i];
		end = corner[(i + 1) % 4];
		start.color = GREEN;
		end.color = GREEN;
		if (!start.hidden && !end.hidden)
			ft_prep_draw_line(img, start, end);
		end = corner[i + 4];
		start.color = BLUE;
		end.color = BLUE;
		if (!start.hidden && !end.hidden)
			ft_prep_draw_line(img, start, end);
		start = corner[i + 4];
		end = corner[((i + 1) % 4) + 4];
		start.color = RED;
		end.color = RED;
		if (!start.hidden && !end.hidden)
			ft_prep_draw_line(img, start, end);
	}
}
