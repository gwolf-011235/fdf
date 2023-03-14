/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoarray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:46:41 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/14 01:51:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

int	ft_count_digit(int num)
{
	int	i;

	if (num == 0)
		i = 1;
	else
		i = 0;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

void	ft_str_rev(char *str)
{
	int		len;
    int		i;
	int		end;
	char	temp;

	len = ft_strlen(str);
	i = 0;
	end = len - 1;
    while (i < end)
	{
        temp = str[i];
        str[i] = str[end];
        str[end] = temp;
		i++;
		end--;
    }
}

void	ft_ftoa_in_place(float num, char *str, int precision)
{
	int		integer_part;
	float	fractional_part;
	int		i;
	int		digit;
	
	integer_part = (int)num;
	fractional_part = num - integer_part;
    i = 0;
	str[i++] = integer_part % 10 + '0';
	integer_part /= 10;
	while (integer_part > 0)
	{
		str[i++] = integer_part % 10 + '0';
		integer_part /= 10;
	}
	ft_str_rev(str);
	str[i++] = '.';
	while (precision-- > 0)
	{
        fractional_part *= 10;
        digit = (int)fractional_part;
        str[i++] = digit + '0';
        fractional_part -= digit;
    }
    str[i] = '\0';
}

void	ft_itoa_in_place(int num, char *str)
{
	int	i;
    int	is_negative;

	i = 0;
	if (num < 0)
	{
        is_negative = 1;
        num = -num;
    }
	else
		is_negative = 0;
	str[i++] = num % 10 + '0';
	num /= 10;
	while (num > 0)
	{
		str[i++] = num % 10 + '0';
		num /= 10;
	}
	if (is_negative)
		str[i++] = '-';
	ft_str_rev(str);
    str[i] = '\0';
}
