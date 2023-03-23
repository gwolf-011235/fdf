/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 20:39:47 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/19 20:40:52 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_mlx_put_int(t_data *data, int pos[2], int num, int pad)
{
	int		numlen;
	char	str[8];

	if (num < 0)
		numlen = 1;
	else
		numlen = 0;
	numlen += ft_count_digit(num);
	if (numlen > 7)
	{
		mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, "max");
		return ;
	}
	ft_memset(str, 0, 8);
	pad -= numlen;
	if (pad > 0)
	{
		ft_itoa_in_place(num, str + pad);
		while (pad--)
			str[pad] = ' ';
	}
	else
		ft_itoa_in_place(num, str);
	mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, str);
}

void	ft_mlx_put_float(t_data *data, int pos[2], float num, int prec)
{
	int		numlen;
	char	str[8];
	int		padding;

	if (num < 0)
		numlen = 1;
	else
		numlen = 0;
	numlen += ft_count_digit(num);
	if (numlen > 3)
	{
		mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, "max");
		return ;
	}
	ft_memset(str, 0, 8);
	padding = 3 - numlen;
	ft_ftoa_in_place(num, str + padding, prec);
	while (padding--)
		str[padding] = ' ';
	mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, str);
}

void	ft_mlx_put_viewname(t_data *data, uint8_t index, int pos[2])
{
	char				str[5];
	static const char	views[5][5] = {
		"None", "Iso", "Top", "Side", "Nice"};

	ft_memset(str, 0, 5);
	ft_strlcpy(str, views[index], 5);
	mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, str);
}

void	ft_mlx_put_colorscheme(t_data *data, uint8_t index, int pos[2])
{
	char				str[7];
	static const char	colorscheme[5][7] = {
		"Init", "B & W", "Ruppi", "Matrix", "Pop"};

	ft_memset(str, 0, 7);
	ft_strlcpy(str, colorscheme[index], 7);
	mlx_string_put(data->mlx, data->win, pos[X], pos[Y], 0x0, str);
}
