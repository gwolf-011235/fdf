/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:11:11 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/08 16:45:32 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_move_atoi(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '-')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

int	ft_hex_to_decimal(char *line, int len)
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
