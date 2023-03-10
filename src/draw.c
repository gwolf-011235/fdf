/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:58:18 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/12 08:29:10 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_pix_to_image(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * img->bytes);
	*(unsigned int *)dst = color;
}

void	ft_draw_wirelines(t_img *img, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->sum_points)
	{
		ft_connect_points(img, &map->morph[i], i / map->width, map);
		i += map->width * map->skip;
	}
}

void	ft_connect_points(t_img *img, t_vec3f *morph_p, int line, t_map *map)
{
	int	i;
	int	end[2];

	i = 0;
	while (i < map->width)
	{
		end[X] = i + map->skip;
		if (end[X] >= map->width)
			end[X] = map->width - 1;
		if (!morph_p[i].hidden || !morph_p[end[X]].hidden)
			ft_prep_draw_line(img, morph_p[i], morph_p[end[X]],
				map->props.canvas);
		end[Y] = i + map->width * map->skip;
		if (line + map->skip >= map->height)
			end[Y] = i + (map->height - 1 - line) * map->width;
		if (!morph_p[i].hidden || !morph_p[end[Y]].hidden)
			ft_prep_draw_line(img, morph_p[i], morph_p[end[Y]],
				map->props.canvas);
		i += map->skip;
	}
}

void	fill_background(t_img *img, int color, int size[2])
{
	int		i;
	char	*dst;
	int		pixel;

	i = 0;
	pixel = size[X] * size[Y];
	dst = img->addr;
	while (i < pixel)
	{
		*(unsigned int *)dst = color;
		dst += img->bytes;
		i++;
	}
}

void	ft_draw_points(t_img *img, t_map *map)
{
	int		i;
	t_pixel	pixel;

	i = 0;
	while (i < map->sum_points)
	{
		if (!map->morph[i].hidden)
		{
			pixel.x = map->morph[i].x;
			pixel.y = map->morph[i].y;
			pixel.color = map->morph[i].color;
			ft_put_pix_to_image(img, pixel.x, pixel.y, pixel.color);
		}
		i++;
	}
}
