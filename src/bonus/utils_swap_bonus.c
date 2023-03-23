/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_swap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:50:56 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 17:39:16 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_swap_img_ptr(t_img **a, t_img **b)
{
	t_img	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_points(t_vec3f *start, t_vec3f *end)
{
	t_vec3f	temp;

	temp = *end;
	*end = *start;
	*start = temp;
}
