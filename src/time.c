/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:35:23 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/07 22:51:31 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/time.h>
#include <stdint.h>

uint64_t	ft_get_timeofday_ms(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	ft_timestamp_ms(t_img *img)
{
	if (img->created_at == 0)
		img->created_at = ft_get_timeofday_ms();
	return (ft_get_timeofday_ms() - img->created_at);
}
