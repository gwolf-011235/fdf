/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:58:18 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/26 11:25:34 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "unistd.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bit_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_triangle(t_data *img, int x, int y, int size)
{
	int trgb = create_trgb(0, 0, 255, 255);
	int size_x = size + x;
	int size_y = size + y;
	int cutoff = size + x;
	int j = y;

	while (x < size_x)
	{
		y = j;
		while (y < size_y)
		{
			if (y < cutoff)
				my_mlx_pixel_put(img, x, y, trgb);
			y++;
		}
		cutoff--;
		x++;
	}
}

void draw_square(t_data *img, int x, int y, int size, int trgb)
{
	int temp;
	int size_x = size + x;
	int size_y = size + y;
	printf("trgb is: %d\n", trgb);

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
