/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:22:48 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 17:38:42 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_hex_to_dec(char *line, int len)
{
	int		i;
	int		decimal;
	char	curr;

	i = 0;
	decimal = 0;
	while (i < len)
	{
		curr = line[i];
		if (ft_isdigit(curr))
			decimal += (curr - '0') * pow(16, len - i - 1);
		else
		{
			curr = ft_tolower(curr);
			decimal += (curr - 'a' + 10) * pow(16, len - i - 1);
		}
		i++;
	}
	return (decimal);
}

int	ft_wrap_angle(float angle, int factor)
{
	angle += factor;
	if (angle < 0)
		angle = 360 + factor;
	if (angle > 360)
		angle = 0 + factor;
	return (angle);
}
