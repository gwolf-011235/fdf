/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:38:32 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/12 08:15:11 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_prep_draw_line(t_img *img, t_vec3f start, t_vec3f end, int size[2])
{
	t_bresvars	vars;

	if (!start.hidden && end.hidden)
		ft_clip_line(&start, &end, size);
	else if (start.hidden && !end.hidden)
	{
		ft_swap_points(&start, &end);
		ft_clip_line(&start, &end, size);
	}
	if (ft_init_bresvars(&vars, start, end))
		return ;
	ft_draw_line(img, &vars);
}

int	ft_init_bresvars(t_bresvars *vars, t_vec3f start, t_vec3f end)
{
	vars->start.x = start.x;
	vars->start.y = start.y;
	vars->start.color = start.color;
	vars->end.x = end.x;
	vars->end.y = end.y;
	vars->end.color = end.color;
	vars->delta.x = abs(vars->end.x - vars->start.x);
	vars->delta.y = abs(vars->end.y - vars->start.y);
	vars->delta.color = start.color;
	if (vars->start.x < vars->end.x)
		vars->step[X] = 1;
	else
		vars->step[X] = -1;
	if (vars->start.y < vars->end.y)
		vars->step[Y] = 1;
	else
		vars->step[Y] = -1;
	vars->error[0] = vars->delta.x - vars->delta.y;
	vars->len = sqrt(vars->delta.x * vars->delta.x \
			+ vars->delta.y * vars->delta.y);
	if (!vars->len)
		return (1);
	vars->remain = vars->len;
	return (0);
}

void	ft_draw_line(t_img *img, t_bresvars *vars)
{
	while (1)
	{
		vars->start.color = ft_gradient(vars->delta.color, vars->end.color,
				vars->len, vars->len - vars->remain);
		ft_put_pix_to_image(img, vars->start.x, vars->start.y,
			vars->start.color);
		if (vars->start.x == vars->end.x
			&& vars->start.y == vars->end.y)
			break ;
		vars->error[1] = vars->error[0] * 2;
		if (vars->error[1] > -vars->delta.y)
		{
			vars->error[0] -= vars->delta.y;
			vars->start.x += vars->step[X];
		}
		if (vars->error[1] < vars->delta.x)
		{
			vars->error[0] += vars->delta.x;
			vars->start.y += vars->step[Y];
		}
		vars->remain -= 1;
	}
}
