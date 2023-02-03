/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:29:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/03 09:16:15 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int get_b(int trgb)
{
	return (trgb & 0xFF);
}

int add_shade(double distance, int trgb)
{
	int rs;
	int gs;
	int bs;

	rs = get_r(trgb) * (1 - distance);
	gs = get_g(trgb) * (1 - distance);
	bs = get_b(trgb) * (1 - distance);
	return (create_trgb(0, rs, gs, bs));
}

int get_opposite(int trgb)
{
	return (trgb ^ 0x00FFFFFF);
}

int	gradient(int color_start, int color_end, double len, double pos)
{
	int factor[3];
	int new_col[3];

	factor[0] = (get_r(color_end) - get_r(color_start)) / len;
	factor[1] = (get_g(color_end) - get_g(color_start)) / len;
	factor[2] = (get_b(color_end) - get_b(color_start)) / len;
	new_col[0] = factor[0] * pos + get_r(color_start);
	new_col[1] = factor[1] * pos + get_g(color_start);
	new_col[2] = factor[2] * pos + get_b(color_start);
	return (create_trgb(0, new_col[0], new_col[1], new_col[2]));
}
