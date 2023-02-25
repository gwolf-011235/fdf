/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:58:18 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/25 22:13:08 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * img->bytes);
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

void	fill_background(t_img *img, int color)
{
	int i;
	int j;
	char *dst;

	i = 0;
	while (i < img->size[X])
	{
		j = 0;
		while (j < img->size[Y])
		{
			dst = img->addr + (j * img->line_len + i * img->bytes);
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

int	ft_is_outside(t_vec3f point, int canvas[2], float padding)
{
	float	pad_x;
	float	pad_y;

	pad_x = canvas[X] * padding;
	pad_y = canvas[Y] * padding;

	if (point.x < (0 + pad_x) || point.x > (canvas[X] - pad_x))
		return (1);
	if (point.y < (0 + pad_y) || point.y > (canvas[Y] - pad_y))
		return (1);
	return (0);
}

int	ft_is_inside(t_point point, int win_x, int win_y)
{
	if (point.x < 0 || point.x > win_x)
		return (0);
	if (point.y < 0 || point.y > win_y)
		return (0);
	return (1);
}

void	draw_points(t_img *img, t_map *map)
{
	int		i;
	t_point	pixel;

	i = 0;
	while (i < map->sum_points)
	{
		pixel = map->pixel[i];
		if (ft_is_inside(pixel, img->size[X], img->size[Y]))
			my_mlx_pixel_put(img, pixel.x, pixel.y, pixel.color);
		i++;
	}
}

int	init_line(t_line *line, t_vec3f start, t_vec3f end)
{
	line->point[0].x = start.x;
	line->point[0].y = start.y;
	line->point[0].color = start.color;
	line->point[1].x = end.x;
	line->point[1].y = end.y;
	line->point[1].color = end.color;
	line->delta[X] = abs(line->point[1].x - line->point[0].x);
	line->delta[Y] = abs(line->point[1].y - line->point[0].y);
	if (line->point[0].x < line->point[1].x)
		line->step[X] = 1;
	else
		line->step[X] = -1;
	if (line->point[0].y < line->point[1].y)
		line->step[Y] = 1;
	else
		line->step[Y] = -1;
	line->error[0] = line->delta[X] - line->delta[Y];
	line->len = sqrt(line->delta[X] * line->delta[X] \
			+ line->delta[Y] * line->delta[Y]);
	if (!line->len)
		return (1);
	line->remain = line->len;
	line->increment = (end.color - start.color) / line->len;
	return (0);
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

void	draw_line(t_img *img, t_vec3f start, t_vec3f end)
{
	t_line	line;

	if (init_line(&line, start, end))
		return ;
	while (line.remain)
	{
		line.factor = (line.len - line.remain) / line.len;
		line.point[0].color = start.color + line.increment * line.factor;
		my_mlx_pixel_put(img, line.point[0].x, line.point[0].y, line.point[0].color);
		if (line.point[0].x == line.point[1].x && line.point[0].y == line.point[1].y)
			break ;
		line.error[1] = line.error[0] * 2;
		if (line.error[1] > -line.delta[Y])
		{
			line.error[0] -= line.delta[Y];
			line.point[0].x += line.step[X];
		}
		if (line.error[1] < line.delta[X])
		{
			line.error[0] += line.delta[X];
			line.point[0].y += line.step[Y];
		}
		line.remain--;
	}
}

void	ft_clip_line(t_vec3f start, t_vec3f end, int size[2], t_img *img)
{
	t_vec3f	temp;
	float	move;

	if (start.hidden)
	{
		temp = end;
		end = start;
		start = temp;		
	}
	if (end.x < 0 || end.x > size[X])
	{
		if (end.x < 0)
			move = (0 - start.x) / (end.x - start.x);
		if (end.x > size[X])
			move = (size[X] - start.x) / (end.x - start.x);
		end.y = start.y + move * (end.y - start.y);
		if (end.x > size[X])
			end.x = size[X];
		if (end.x < 0)
			end.x = 0;
	}
	if (end.y < 0 || end.y > size[Y])
	{
		if (end.y < 0)
			move = (0 - start.y) / (end.y - start.y);
		if (end.y > size[Y])
			move = (size[Y] - start.y) / (end.y - start.y);
		end.x = start.x + move * (end.x - start.x);
		if (end.y > size[Y])
			end.y = size[Y];
		if (end.y < 0)
			end.y = 0;
	}
	draw_line(img, start, end);
}

void	lines(t_img *img, t_map *map)
{
	int		i;
	t_vec3f	start;
	t_vec3f	end;

	i = 0;
	while (i < map->sum_points)
	{
		start = map->morph[i + i];
		if (i % map->width != map->width - 1)
		{
			end = map->morph[i + i + 2];
			if (!start.hidden && !end.hidden)
				draw_line(img, start, end);
			else if ((start.hidden && !end.hidden) || (!start.hidden && end.hidden))
				ft_clip_line(start, end, img->size, img);
		}
		if (i / map->width != map->height - 1)
		{
			end = map->morph[i + i + map->width * 2];
			if (!start.hidden && !end.hidden)
				draw_line(img, start, end);
			else if ((start.hidden && !end.hidden) || (!start.hidden && end.hidden))
				ft_clip_line(start, end, img->size, img);
		}
		i++;
	}
}
