/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:29:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/23 15:38:24 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	ft_alpha_blend(int new_color, int old_color)
{
	int	start[4];
	int	invert[4];
	int	blend[3];

	start[0] = (new_color & 0xFF000000) >> 24;
	start[1] = ((new_color & 0x00FF0000) >> 16) * start[0] / 255;
	start[2] = ((new_color & 0x0000FF00) >> 8) * start[0] / 255;
	start[3] = (new_color & 0x000000FF) * start[0] / 255;
	invert[0] = 255 - start[0];
	invert[1] = ((old_color & 0x00FF0000) >> 16) * invert[0] / 255;
	invert[2] = ((old_color & 0x0000FF00) >> 8) * invert[0] / 255;
	invert[3] = (old_color & 0x000000FF) * invert[0] / 255;
	blend[0] = start[1] + invert[1];
	blend[1] = start[2] + invert[2];
	blend[2] = start[3] + invert[3];
	return ((start[0] << 24) | (blend[0] << 16) | (blend[1] << 8) | blend[2]);
}

int	gradient(int color_start, int color_end, double len, double pos)
{
	int	factor[3];
	int	new_col[3];

	factor[0] = ((color_end >> 16 & 0xFF) - (color_start >> 16 & 0xFF)) / len;
	factor[1] = ((color_end >> 8 & 0xFF) - (color_start >> 8 & 0xFF)) / len;
	factor[2] = ((color_end & 0xFF) - (color_start & 0xFF)) / len;
	new_col[0] = factor[0] * pos + (color_start >> 16 & 0xFF);
	new_col[1] = factor[1] * pos + (color_start >> 8 & 0xFF);
	new_col[2] = factor[2] * pos + (color_start & 0xFF);
	return (create_trgb(0, new_col[0], new_col[1], new_col[2]));
}

void	ft_set_pattern(int pattern[3], int choice)
{
	const int colorschemes[3][3] = {
		{RED, YELLOW, BLUE},
		{PURPLE, GREEN, ORANGE},
		{LIGHTBLUE, PINK, LIME}
	};

	pattern[0] = colorschemes[choice][0];
	pattern[1] = colorschemes[choice][1];
	pattern[2] = colorschemes[choice][2];
}
