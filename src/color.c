/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:29:34 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/05 21:55:23 by gwolf            ###   ########.fr       */
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

void	ft_set_pattern(int pattern[4], int choice, int specific)
{
	const int	colorschemes[4][4] = {
	{YELLOW, RED, BLUE, BLACK},
	{RED, BLACK, GREEN, WHITE},
	{LIGHTBLUE, PINK, LIME, LIGHT_GRAY},
	{D_GREEN, D_PURPLE, D_RED, D_GREY}
	};

	if (specific == 5)
	{
		pattern[0] = colorschemes[choice][0];
		pattern[1] = colorschemes[choice][1];
		pattern[2] = colorschemes[choice][2];
		pattern[3] = colorschemes[choice][3];
		return ;
	}
	if (specific == 0)
		pattern[0] = colorschemes[choice][0];
	else if (specific == 1)
		pattern[1] = colorschemes[choice][0];
	else if (specific == 2)
		pattern[2] = colorschemes[choice][0];
	else if (specific == 3)
		pattern[3] = colorschemes[choice][0];
}
