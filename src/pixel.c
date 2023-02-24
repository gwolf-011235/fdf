/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 07:38:00 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/24 21:28:12 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_pixel(t_vec3f *morph, t_point *pixel, int sum)
{
	int	i;

	i = 0;
	while (i < sum + 8)
	{
		pixel[i].x = floor(morph[i + i].x);
		pixel[i].y = floor(morph[i + i].y);
		pixel[i].color = morph[i + i].color;
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


