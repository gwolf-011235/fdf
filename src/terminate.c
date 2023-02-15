/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:46:48 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/15 16:38:37 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

void	ft_terminate(char *message)
{
	if (errno == 0)
		ft_putendl_fd(message, 2);
	else
		perror(message);
	exit(1);
}

void	ft_free_rows(char *row, char *rows[ROW_MAX], int fd)
{
	int	i;

	close(fd);
	get_next_line(fd);
	free(row);
	i = ROW_MAX;
	while (i--)
	{
		free(rows[i]);
	}
	ft_terminate(ERR_BIG);
}

void	ft_mlx_free(t_data *data, t_map *map)
{
	if (data)
	{
		if (data->render.ptr)
			mlx_destroy_image(data->mlx, data->render.ptr);
		if (data->menu.ptr)
			mlx_destroy_image(data->mlx, data->menu.ptr);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
	}
	if (map)
	{
		free(map->points);
		free(map->color_array);
	}

}
