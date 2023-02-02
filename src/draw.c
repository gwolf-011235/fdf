/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:58:18 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/02 14:42:55 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bit_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	fill_background(t_img *img)
{
	int i = 0;
	int j = 0;

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

void draw_points(t_img *img, t_map *map)
{
	int i;
	int trgb = create_trgb(0, 255, 0, 0);

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

void draw_triangle(t_img *img, int x, int y, int size)
{
	int trgb = create_trgb(0, 0, 255, 255);
	int size_x = size + x;
	int size_y = size + y;
	//int cutoff = size + x;
	int temp = y;

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

void draw_square(t_img *img, int x, int y, int size, int trgb)
{
	int temp;
	int size_x = size + x;
	int size_y = size + y;

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

void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color) 
{
    // The Bresenham algorithm uses the concept of "error" to determine which pixels to draw
    int dx = abs(x1 - x0); // delta x, the difference between x1 and x0
    int dy = abs(y1 - y0); // delta y, the difference between y1 and y0
    int sx = x0 < x1 ? 1 : -1; // step in x direction, either 1 or -1
    int sy = y0 < y1 ? 1 : -1; // step in y direction, either 1 or -1
    int err = dx - dy; // initial error value

    // Draw pixels using the Bresenham algorithm
    while (1) {
        // Draw a pixel at the current position
        my_mlx_pixel_put(img, x0, y0, color);
        // If we've reached the end point, exit the loop
        if (x0 == x1 && y0 == y1) {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void	lines(t_img *img, t_map *map)
{
	int i;

	i = 0;
	while (i < map->sum_points - 1)
	{
		if (i % map->width != map->width - 1)
			draw_line(img, map->morph[i].x, map->morph[i].y, map->morph[i + 1].x, map->morph[i + 1].y, create_trgb(0, 0, 0, 255));
		if (i / map->width != map->height - 1)
			draw_line(img, map->morph[i].x, map->morph[i].y, map->morph[i + map->width].x, map->morph[i + map->width].y, create_trgb(0, 0, 0, 255));
		i++;
	}
}
