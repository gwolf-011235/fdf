/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:20:50 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 15:51:06 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_data(t_data *data)
{
	ft_set_pattern(data->map.pattern, 0);
	data->map.props.view = ISO;
	data->map.sampling = 1;
	ft_set_ft_ptr(data, 0);
	ft_set_ft_ptr(data, 2);
}

int	ft_close_program(t_data *data)
{
	ft_free_mlx(data, CYA, false);
	exit(0);
}
