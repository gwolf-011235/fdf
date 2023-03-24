/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:35:23 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/24 19:11:17 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

uint64_t	ft_get_timeofday_ms(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	ft_timestamp_ms(uint64_t created_at)
{
	return (ft_get_timeofday_ms() - created_at);
}

bool	ft_check_fps(t_data *data)
{
	static uint64_t	last_update;

	data->fps = (ft_timestamp_ms(data->created_at) - last_update);
	if (data->fps < (uint64_t)(1000 / FPS_TARGET))
		return (true);
	last_update = ft_timestamp_ms(data->created_at);
	return (false);
}
