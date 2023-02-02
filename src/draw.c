/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:58:18 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/02 16:02:01 by gwolf            ###   ########.fr       */
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
			my_mlx_pixel_put(img, i, j, create_trgb(0, 0, 255, 0));
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

void	init_line(t_po_int start, t_po_int end, t_po_int *delta, t_po_int *step)
{
	delta->x = abs(end.x - start.x);
	delta->y = abs(end.y - start.y);
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

void	draw_line(t_img *img, t_po_int start, t_po_int end, int color)
{
	t_po_int	delta;
	t_po_int	step;
	int			err;
	int			e2;

	init_line(start, end, &delta, &step);
	err = delta.x - delta.y;
	while (1)
	{
		my_mlx_pixel_put(img, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 > -delta.y)
		{
			err -= delta.y;
			start.x += step.x;
		}
		if (e2 < delta.x)
		{
			err += delta.x;
			start.y += step.y;
		}
	}
}

void	lines(t_img *img, t_map *map)
{
	int			i;
	t_po_int	start;
	t_po_int	end;

	i = 0;
	while (i < map->sum_points - 1)
	{
		start.x = map->morph[i].x;
		start.y = map->morph[i].y;
		if (i % map->width != map->width - 1)
		{
			end.x = map->morph[i + 1].x;
			end.y = map->morph[i + 1].y;
			draw_line(img, start, end, create_trgb(0, 0, 0, 255));
		}
		if (i / map->width != map->height - 1)
		{
			end.x = map->morph[i + map->width].x;
			end.y = map->morph[i + map->width].y;
			draw_line(img, start, end, create_trgb(0, 0, 0, 255));
		}
		i++;
	}
}
