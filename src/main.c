/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:54:09 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/27 14:07:18 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char *argv[])
{
	static t_map map;

	if (argc != 2)
		terminate(ERR_ARGS);
	parse_map(&map, argv[1]);

	testwindow(&map);
}
