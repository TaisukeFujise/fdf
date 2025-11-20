/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:39:11 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/20 10:39:14 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	print_mappoint(t_map map)
{
	int i;

	i = 0;
	while (i < map.width * map.height)
	{
		printf("i : %d\n", i);
		printf("(x, y, z) = (%f, %f, %f)\n", map.points[i].x, map.points[i].y, map.points[i].z);
		i++;
	}
}

void	print_map_spoint(t_map map)
{
	int i;

	i = 0;
	while (i < map.width * map.height)
	{
		printf("i: %d\n", i);
		printf("(screen_x, screen_y) = (%f, %f)\n", map.points[i].screen_x, map.points[i].screen_y);
		i++;
	}
}
