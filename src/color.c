/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:29:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/09 14:16:54 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	gradient(int start, int end, double len, double pos)
{
	int		factor[4];
	int		n_col[4];
	double	invert_len;

	invert_len = 1.0 / len;
	factor[0] = ((end >> 24 & 0xFF) - (start >> 24 & 0xFF)) * invert_len;
	factor[1] = ((end >> 16 & 0xFF) - (start >> 16 & 0xFF)) * invert_len;
	factor[2] = ((end >> 8 & 0xFF) - (start >> 8 & 0xFF)) * invert_len;
	factor[3] = ((end & 0xFF) - (start & 0xFF)) * invert_len;
	n_col[0] = factor[0] * pos + (start >> 24 & 0xFF);
	n_col[1] = factor[1] * pos + (start >> 16 & 0xFF);
	n_col[2] = factor[2] * pos + (start >> 8 & 0xFF);
	n_col[3] = factor[3] * pos + (start & 0xFF);
	return ((n_col[0] << 24) | (n_col[1] << 16) | (n_col[2] << 8) | n_col[3]);
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
