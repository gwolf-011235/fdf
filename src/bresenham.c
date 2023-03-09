/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:38:32 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/09 19:21:43 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_init_line(t_line *line, t_vec3f start, t_vec3f end)
{
	line->start.x = start.x;
	line->start.y = start.y;
	line->start.color = start.color;
	line->end.x = end.x;
	line->end.y = end.y;
	line->end.color = end.color;
	line->delta.x = abs(line->end.x - line->start.x);
	line->delta.y = abs(line->end.y - line->start.y);
	line->delta.color = start.color;
	if (line->start.x < line->end.x)
		line->step[X] = 1;
	else
		line->step[X] = -1;
	if (line->start.y < line->end.y)
		line->step[Y] = 1;
	else
		line->step[Y] = -1;
	line->error[0] = line->delta.x - line->delta.y;
	line->len = sqrt(line->delta.x * line->delta.x \
			+ line->delta.y * line->delta.y);
	if (!line->len)
		return (1);
	line->remain = line->len;
	return (0);
}

void	ft_prep_bresenham(t_img *img, t_vec3f start, t_vec3f end)
{
	t_line	line;

	if (ft_init_line(&line, start, end))
		return ;
	ft_draw_line(img, &line);
}

void	ft_draw_line(t_img *img, t_line *line)
{
	while (1)
	{
		line->start.color = gradient(line->delta.color, line->end.color,
				line->len, line->len - line->remain);
		my_mlx_pixel_put(img, line->start.x, line->start.y,
			line->start.color);
		if (line->start.x == line->end.x
			&& line->start.y == line->end.y)
			break ;
		line->error[1] = line->error[0] * 2;
		if (line->error[1] > -line->delta.y)
		{
			line->error[0] -= line->delta.y;
			line->start.x += line->step[X];
		}
		if (line->error[1] < line->delta.x)
		{
			line->error[0] += line->delta.x;
			line->start.y += line->step[Y];
		}
		line->remain--;
	}
}
