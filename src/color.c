/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:29:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/10 09:45:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	gradient(int start, int end, double len, double pos)
{
	t_color	one;
	t_color	two;
	t_color	ret;
	double	t;

	t = pos / len;

	one.a = (start >> 24 & 0xFF);
	one.r = (start >> 16 & 0xFF);
	one.g = (start >> 8 & 0xFF);
	one.b = (start & 0xFF);
	two.a = (end >> 24 & 0xFF);
	two.r = (end >> 16 & 0xFF);
	two.g = (end >> 8 & 0xFF);
	two.b = (end & 0xFF);
	ret.a = one.a + t * (two.a - one.a);
	ret.r = one.r + t * (two.r - one.r);
	ret.g = one.g + t * (two.g - one.g);
	ret.b = one.b + t * (two.b - one.b);
	return ((ret.a << 24) | (ret.r << 16) | (ret.g << 8) | ret.b);
}

void	ft_set_pattern(int pattern[4], int choice)
{
	static const int	colorschemes[5][4] = {
	{YELLOW, RED, BLUE, BLACK},
	{BLACK, BLACK, BLACK, WHITE},
	{TYRES, MICHELIN, BLACK, TOKYODRIFT},
	{BLACK, GREEN, BLACK, BLACK},
	{PURPLE, ORANGE, PINK, LIGHTBLUE}
	};

	pattern[0] = colorschemes[choice][0];
	pattern[1] = colorschemes[choice][1];
	pattern[2] = colorschemes[choice][2];
	pattern[3] = colorschemes[choice][3];
}
