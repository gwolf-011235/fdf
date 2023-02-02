/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:58:18 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/02 10:34:46 by gwolf            ###   ########.fr       */
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

void draw_points(t_img *img, t_map *map)
{
	int i = 0;
	int max = map->width * map->height;
	double zoom = 10;
	double offset_x = WIN_X / 2;
	double offset_y = WIN_Y / 2;
	int x;
	int y;
	int trgb = create_trgb(0, 255, 0, 0);
	double project[3][3] = {
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 0}
	};

	while (i < max)
	{
		map->morph[i] = rotate_z(map->morph[i], 1);
		map->morph[i] = matrix_point(project, map->morph[i]);
		x = map->morph[i].x * zoom + offset_x;
		y = map->morph[i].y * zoom + offset_y;
		my_mlx_pixel_put(img, x, y, trgb);
		//draw_square(img, x, y, 1, trgb);
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

