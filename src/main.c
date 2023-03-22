/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:54:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/22 10:07:37 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_ft_ptr(t_data *data, int choose)
{
	static const t_calc_ft	calc_ptr[2] = {ft_calc_morph, ft_wobble};
	static const t_draw_ft	draw_ptr[2] = {ft_draw_wirelines, ft_draw_points};

	if (choose == 0)
		data->calc_ft = calc_ptr[0];
	else if (choose == 1)
		data->calc_ft = calc_ptr[1];
	else if (choose == 2)
		data->draw_ft = draw_ptr[0];
	else if (choose == 3)
		data->draw_ft = draw_ptr[1];
}

int	ft_close_program(t_data *data)
{
	ft_free_mlx(data, CYA, false);
	exit(0);
}

int	main(int argc, char *argv[])
{
	static t_data	data;

	if (argc != 2)
		ft_terminate(ERR_ARGS);
	ft_check_map(&data.map, argv[1]);
	ft_map_init(&data.map);
	ft_parse_map(&data.map);
	ft_set_ft_ptr(&data, 0);
	ft_set_ft_ptr(&data, 2);
	srand(time(NULL));
	ft_init_window(&data);
	ft_init_menu(&data);
	ft_init_project(&data);
	data.created_at = ft_get_timeofday_ms();
	ft_start_mlx_loop(&data);
}
