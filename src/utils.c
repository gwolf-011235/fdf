/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:11:11 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/14 18:47:53 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_move_atoi(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '-')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

int	ft_jump_over_hex(char *line)
{
	int		i;

	i = 0;
	if (line[i] == ',' && line[i + 1] == '0')
		i += 2;
	else
		return (-1);
	if (line[i] != 'x' && line[i] != 'X')
		return (-1);
	i++;
	while (ft_strchr("0123456789ABCDEFabcdef", line[i]))
		i++;
	if (line[i] == ' ' || line[i] == '\n')
		return (i);
	else
		return (-1);
}

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

void	ft_set_view_angle(float angle[3], uint8_t index)
{
	static const float	preset[4][3] = {
		{0, 0, 0}, {35, 0, 45}
	};

	angle[X] = preset[index][X];
	angle[Y] = preset[index][Y];
	angle[Z] = preset[index][Z];
}
