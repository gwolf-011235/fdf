/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:15:46 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/14 01:39:08 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	test(t_data *data)
{
	float	num = 3.145;
	int		num2 = 3650;
	char	str[20];

	(void)data;
	ft_ftoa_in_place(num, str, 5);
	printf("This is str: %s\n", str);
	ft_memset(str, 0, 20);
	ft_itoa_in_place(num2, str);
	printf("This is str2: %s\n", str);
}
