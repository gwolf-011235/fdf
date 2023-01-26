/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:29:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/25 13:30:19 by gwolf            ###   ########.fr       */
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
