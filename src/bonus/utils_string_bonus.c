/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:11:11 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 17:39:08 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
