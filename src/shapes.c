/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 08:44:25 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/19 09:44:03 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	ft_math_pt(t_point one, t_point two, int x, int y)
{
	t_point	ret;

	if (x == 0)
		ret.x = one.x + two.x;
	else if (x == 1)
		ret.x = one.x - two.x;
	else if (x == 2)
		ret.x = one.x + two.y;
	else if (x == 3)
		ret.x = one.x - two.y;
	if (y == 0)
		ret.y = one.y + two.y;
	else if (y == 1)
		ret.y = one.y - two.y;
	else if (y == 2)
		ret.y = one.y + two.x;
	else if (y == 3)
		ret.y = one.y - two.x;
	ret.color = one.color;
	return (ret);
}

void	ft_draw_circle(t_img *img, t_point ctr, int radius)
{
	t_point	out;
	int		d;

	out.x = 0;
	out.y = radius;
	d = 3 - 2 * radius;
	while (out.x <= out.y)
	{
		draw_line(img, ft_math_pt(ctr, out, 0, 0), ft_math_pt(ctr, out, 1, 0));
		draw_line(img, ft_math_pt(ctr, out, 0, 1), ft_math_pt(ctr, out, 1, 1));
		draw_line(img, ft_math_pt(ctr, out, 2, 2), ft_math_pt(ctr, out, 3, 2));
		draw_line(img, ft_math_pt(ctr, out, 2, 3), ft_math_pt(ctr, out, 3, 3));
		out.x++;
		if (d < 0)
			d += 4 * out.x + 6;
		else
		{
			out.y--;
			d += 4 * (out.x - out.y) + 10;
		}
	}
}
