/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:54:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/22 11:17:58 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_data(t_data *data)
{
	ft_set_pattern(data->map.pattern, 0);
	data->map.props.angle[X] = 35;
	data->map.props.angle[Y] = 0;
	data->map.props.angle[Z] = 45;
	data->map.factor = 1;
	data->map.skip = 1;
	data->map.props.scale_z = 0.1;
	ft_set_ft_ptr(data, 0);
	ft_set_ft_ptr(data, 2);
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
	ft_init_data(&data);
	ft_parse_map(&data.map);
	srand(time(NULL));
	ft_init_window(&data);
	ft_init_project(&data);
	data.created_at = ft_get_timeofday_ms();
	ft_start_mlx_loop(&data);
}
