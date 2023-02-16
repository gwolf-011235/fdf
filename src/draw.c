/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:58:18 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/16 21:52:45 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
void	ft_point_to_image(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		blend;

	if (x >= 0 && x < img->size[X] && y >= 0 && y < img->size[Y])
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		blend = ft_alpha_blend(*(unsigned int *)pixel);
	}
}
*/

void	fill_background(t_img *img)
{
	ft_bzero(img->addr, img->size[X] * img->size[Y] * 4);
}

int	ft_is_inside(t_point point, int win_x, int win_y)
{
	if (point.x < 0 || point.x > win_x)
		return (1);
	if (point.y < 0 || point.y > win_y)
		return (1);
	return (0);
}

void	draw_points(t_img *img, t_map *map)
{
	int		i;
	t_point	pixel;

	i = 0;
	while (i < map->sum_points)
	{
		pixel = ft_convert_vec2point(map->points[i D M], map->colors[i]);
		if (ft_is_inside(pixel, img->size[X], img->size[Y]))
			my_mlx_pixel_put(img, pixel.x, pixel.y, pixel.color);
		i++;
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

void	init_line(t_point start, t_point end, t_point *delta, t_point *step)
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

void	draw_line(t_img *img, t_point start, t_point end, int colors[2])
{
	t_point	delta;
	t_point	step;
	int			err;
	int			e2;
	int			len;
	int			left;
	int			color;

	init_line(start, end, &delta, &step);
	err = delta.x - delta.y;
	len = sqrt(delta.x * delta.x + delta.y * delta.y);
	left = len;
	while (left)
	{
		color = gradient(colors[0], colors[1], len, len - left);
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
		left--;
	}
}

t_point	ft_convert_vec2point(t_vec3f point, int color)
{
	t_point ret;

	ret.x = floor(point.x);
	ret.y = floor(point.y);
	ret.color = color;
	return (ret);
}

void	lines(t_img *img, t_map *map)
{
	int			i;
	t_point	start;
	t_point	end;
	int			colors[2];

	i = 0;
	while (i < map->sum_points)
	{
		start = ft_convert_3to2(map->points[i D M]);
		colors[0] = map->colors[i];
		if (i % map->width != map->width - 1)
		{
			end = ft_convert_3to2(map->points[i D M + 2]);
			colors[1] = map->colors[i + 1];
			if (!ft_is_outside(map->points[i D M], img->size[X], img->size[Y]) \
					&& !ft_is_outside(map->points[i D M + 2], img->size[X], img->size[Y]))
				draw_line(img, start, end, colors);
		}
		if (i / map->width != map->height - 1)
		{
			end = ft_convert_3to2(map->points[i D M + (map->width * 2)]);
			colors[1] = map->colors[i + map->width];
			if (!ft_is_outside(map->points[i D M], img->size[X], img->size[Y]) \
					&& !ft_is_outside(map->points[i D M + (map->width* 2)], img->size[X], img->size[Y]))
				draw_line(img, start, end, colors);
		}
		i++;
	}
}
