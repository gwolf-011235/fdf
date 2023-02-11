/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 07:10:44 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/11 08:37:39 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_print_mat4(t_mat4 matrix)
{
	int	i;
	int	j;

	ft_printf("\nMatrix is:\n");
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%0.3f\t", matrix[i][j]);
			fflush(stdout);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	ft_print_inverse(float inverse[4][8])
{
	int i;
	int j;

	ft_printf("\nInverse Matrix is:\n");
	i = 0;
	while (i < 4)
	{
		j = 4;
		while (j < 2*4)
		{
			printf("%0.3f\t", inverse[i][j]);
			fflush(stdout);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	ft_print_point(t_vec3f point)
{
	ft_printf("\nPoint is:\n");
	printf("x : %0.3f\n", point.x);
	printf("y : %0.3f\n", point.y);
	printf("z : %0.3f\n", point.z);
}
