/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf < gwolf@student.42vienna.com >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:58:18 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/31 13:30:34 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_pix_to_image(t_img *img, int x, int y, int color)
{
	int		i;
	char	*pixel;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * img->bytes);
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	ft_draw_wirelines(t_img *img, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->sum_points)
	{
		ft_connect_points(img, &map->morph[i], i / map->width, map);
		i += map->width * map->sampling;
	}
}

void	ft_connect_points(t_img *img, t_vec3f *morph_p, int line, t_map *map)
{
	int	i;
	int	end[2];

	i = 0;
	while (i < map->width)
	{
		end[X] = i + map->sampling;
		if (end[X] >= map->width)
			end[X] = map->width - 1;
		if (!morph_p[i].hidden && !morph_p[end[X]].hidden)
			ft_prep_draw_line(img, morph_p[i], morph_p[end[X]]);
		end[Y] = i + map->width * map->sampling;
		if (line + map->sampling >= map->height)
			end[Y] = i + (map->height - 1 - line) * map->width;
		if (!morph_p[i].hidden && !morph_p[end[Y]].hidden)
			ft_prep_draw_line(img, morph_p[i], morph_p[end[Y]]);
		i += map->sampling;
	}
}
