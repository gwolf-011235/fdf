/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:46:48 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/23 15:53:36 by gwolf            ###   ########.fr       */
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

void	ft_free_rows(char *row, char *rows[ROW_MAX], int fd, int num)
{
	int	i;

	close(fd);
	get_next_line(fd);
	errno = 0;
	free(row);
	i = num;
	while (i--)
	{
		free(rows[i]);
	}
	if (num == ROW_MAX)
	{
		ft_printf("Max row is: %d\n", ROW_MAX);
		ft_terminate(ERR_BIG);
	}
	ft_terminate(ERR_READ);
}

void	ft_free_map_ptr(t_map *map, char *string)
{
	if (map->points)
		free(map->points);
	ft_terminate(string);
}

void	ft_free_mlx(t_data *data, char *string, bool error)
{
	free(data->map.points);
	mlx_destroy_image(data->mlx, data->render.ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (error)
		ft_terminate(string);
	else
		ft_putendl_fd(string, 1);
}
