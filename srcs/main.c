/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 09:29:34 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/18 23:58:46 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

void	print_map(t_map map)
{
	printf("==map==\n");
	printf("width: %d\n", map.width);
	printf("height: %d\n", map.height);
}

void	print_mappoint(t_map map)
{
	int i;

	i = 0;
	while (i < map.width * map.height)
	{
		printf("==dot==\n");
		printf("x: %f\n", map.points[i].x);
		printf("y: %f\n", map.points[i].y);
		printf("z: %f\n", map.points[i].z);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid Argument\n", 1), 1);
	if (ctx_init(&ctx) == ERROR)
		return (free_ctx(&ctx), 1);
	if (parse_map(&ctx, argv[1]) == ERROR)
		return (free_ctx(&ctx), 1);
	// print_map(ctx.map);
	// print_mappoint(ctx.map);
	// my_mlx_pixel_put(&(ctx.img.img), i, j, color); 
	
	/* camera構造体の更新 */
	/* (x, y, z) -> (screen_x, screen_y)への変換 */

	/* */
	mlx_put_image_to_window(ctx.mlx, ctx.win, ctx.img.img, 0, 0);
	setup_hooks(&ctx);
	mlx_loop(ctx.mlx);
}
