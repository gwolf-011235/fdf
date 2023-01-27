/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:58:18 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/27 16:42:37 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bit_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_points(t_data *img, t_map *map)
{
	int i = 0;
	int max = map->width * map->width;
	int zoom = 30;
	int x;
	int y;
	int trgb = create_trgb(0, 255, 0, 0);

	while (i < max)
	{
		x = map->points[i].x * zoom;
		y = map->points[i].y * zoom;
		draw_square(img, x, y, 10, trgb);
		i++;
		trgb = get_opposite(trgb);
	}
}

void draw_triangle(t_data *img, int x, int y, int size)
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

void draw_square(t_data *img, int x, int y, int size, int trgb)
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

void draw_line(t_data *img, int x0, int y0, int x1, int y1, int color) 
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

