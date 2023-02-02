/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:29:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/02 17:14:49 by gwolf            ###   ########.fr       */
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

int	transition(int color_start, int color_end, double top, double low)
{
	int middle[3];

	if (top)
	{
		middle[0] = (get_r(color_end) - get_r(color_start)) / top;
		middle[1] = (get_g(color_end) - get_g(color_start)) / top;
		middle[2] = (get_b(color_end) - get_b(color_start)) / top;
	}
	else
	{
		middle[0] = (get_r(color_end) - get_r(color_start)) / low;
		middle[1] = (get_g(color_end) - get_g(color_start)) / low;
		middle[2] = (get_b(color_end) - get_b(color_start)) / low;
	}
	return (create_trgb(0, middle[0], middle[1], middle[2]));
}

int get_transition(double z, int transition_color)
{
	int new_col[3];

	new_col[0] = get_r(transition_color) * z + get_r(COLOR_MID);
	new_col[1] = get_g(transition_color) * z + get_g(COLOR_MID);
	new_col[2] = get_b(transition_color) * z + get_b(COLOR_MID);

	return (create_trgb(0, new_col[0], new_col[1], new_col[2]));
}
