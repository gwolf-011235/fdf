/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 07:38:00 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/19 07:39:34 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	ft_convert_vec2point(t_vec3f point, int color)
{
	t_point ret;

	ret.x = floor(point.x);
	ret.y = floor(point.y);
	ret.color = color;
	return (ret);
}

void	ft_init_pixel(t_vec3f *morph, int *colors, t_point *pixel, int sum)
{
	int	i;

	i = 0;
	while (i < sum)
	{
		pixel[i] = ft_convert_vec2point(morph[i + i], colors[i]);
		i++;
	}
	while (i < (sum + 8))
	{
		pixel[i] = ft_convert_vec2point(morph[i + i], RED);
		i++;
	}
}

void	ft_update_pix_point(t_vec3f *morph, t_point *pixel, int sum)
{
	int	i;

	i = 0;
	while (i < (sum + 8))
	{
		pixel[i].x = floor(morph[i + i].x);
		pixel[i].y = floor(morph[i + i].y);
		i++;
	}
}

void	ft_update_pix_color(int *colors, t_point *pixel, int sum)
{
	int	i;

	i = 0;
	while (i < sum)
	{
		pixel[i].color = colors[i];
		i++;
	}
}


