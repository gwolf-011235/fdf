/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:58:18 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/03 14:09:43 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bit_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	fill_background(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_X)
	{
		j = 0;
		while (j < WIN_Y)
		{
			my_mlx_pixel_put(img, i, j, create_trgb(0, 0, 0, 0));
			j++;
		}
		i++;
	}
}

int	ft_is_outside(t_point point)
{
	if (point.x < 0 || point.x > WIN_X)
		return (1);
	if (point.y < 0 || point.y > WIN_Y)
		return (1);
	return (0);
}

void	draw_points(t_img *img, t_map *map)
{
	int	i;
	int	trgb;

	trgb = create_trgb(0, 255, 0, 0);
	i = 0;
	while (i < map->sum_points)
	{
		if (ft_is_outside(map->morph[i]))
		{
			i++;
			continue ;
		}
		my_mlx_pixel_put(img, map->morph[i].x, map->morph[i].y, trgb);
		i++;
		trgb = get_opposite(trgb);
	}
}

void	draw_triangle(t_img *img, int x, int y, int size)
{
	int	trgb;
	int	size_x;
	int	size_y;
	int	temp;

	trgb = create_trgb(0, 0, 255, 255);
	size_x = size + x;
	size_y = size + y;
	while (x < size_x)
	{
		temp = y;
		while (temp < size_y)
		{
			my_mlx_pixel_put(img, x, temp, trgb);
			temp++;
		}
		size_y--;
		x++;
	}
}

void	draw_square(t_img *img, int x, int y, int size, int trgb)
{
	int	temp;
	int	size_x;
	int	size_y;

	size_x = size + x;
	size_y = size + y;
	while (x < size_x)
	{
		temp = y;
		while (temp < size_y)
		{
			my_mlx_pixel_put(img, x, temp, trgb);
			temp++;
		}
		x++;
		if (x % 10 == 0)
			trgb = get_opposite(trgb);
	}
}

void	init_line(t_point start, t_point end, t_po_int *delta, t_po_int *step)
{
	delta->x = abs((int)end.x - (int)start.x);
	delta->y = abs((int)end.y - (int)start.y);
	if (start.x < end.x)
		step->x = 1;
	else
		step->x = -1;
	if (start.y < end.y)
		step->y = 1;
	else
		step->y = -1;
}
/**
 * @brief This function implements the Bresenham algorithm.
 *		  The Bresenham algorithm uses the concept of "error" 
 *		  to determine which pixels to draw
 *
 * @param img: The pointer to the image struct
 * @param start: The startpoint with converted values to int
 * @param end: The endpoint with converted values to int
 * @param color: The color to draw
 */

void	draw_line(t_img *img, t_point start, t_point end)
{
	t_po_int	delta;
	t_po_int	step;
	int			err;
	int			e2;
	int			len;
	int			left;
	int			color;
	int			test[4];

	init_line(start, end, &delta, &step);
	err = delta.x - delta.y;
	len = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	left = len;
	test[0] = start.x;
	test[1] = start.y;
	test[2] = end.x;
	test[3] = end.y;
	while (left)
	{
		color = gradient(start.color, end.color, len, len - left);
		my_mlx_pixel_put(img, test[0], test[1], color);
		if (test[0] == test[2] && test[1] == test[3])
			break ;
		e2 = 2 * err;
		if (e2 > -delta.y)
		{
			err -= delta.y;
			test[0] += step.x;
		}
		if (e2 < delta.x)
		{
			err += delta.x;
			test[1] += step.y;
		}
		left--;
	}
}

void	lines(t_img *img, t_map *map)
{
	int			i;
	t_po_int	start;
	t_po_int	end;

	i = 0;
	while (i < map->sum_points)
	{
		start.x = abs((int)map->morph[i].x);
		start.y = abs((int)map->morph[i].y);
		if (i % map->width != map->width - 1)
		{
			end.x = abs((int)map->morph[i + 1].x);
			end.y = abs((int)map->morph[i + 1].y);
			if (!ft_is_outside(map->morph[i]) && !ft_is_outside(map->morph[i + 1]))
				draw_line(img, map->morph[i], map->morph[i + 1]);
		}
		if (i / map->width != map->height - 1)
		{
			end.x = abs((int)map->morph[i + map->width].x);
			end.y = abs((int)map->morph[i + map->width].y);
			if (!ft_is_outside(map->morph[i]) && !ft_is_outside(map->morph[i + map->width]))
				draw_line(img, map->morph[i], map->morph[i + map->width]);
		}
		i++;
	}
}
