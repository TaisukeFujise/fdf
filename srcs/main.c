/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 09:29:34 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/18 21:23:37 by tafujise         ###   ########.fr       */
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

// void	print_mappoint(t_map map)
// {
// 	int i;

// 	i = 0;
// 	while (i < map.width * map.height)
// 	{
// 		printf("==dot==\n");
// 		printf("x: %f\n", map.points->x);
// 		printf("y: %f\n", map.points->y);
// 		printf("z: %f\n", map.points->z);
// 		map.points++;
// 		i++;
// 	}
// }

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid Argument\n", 1), 1);
	if (ctx_init(&ctx) == ERROR)
		return (printf("af**k\n"), free_ctx(&ctx), 1);
	if (parse_map(&ctx, argv[1]) == ERROR)
		return (printf("bf**k\n"), free_ctx(&ctx), 1);
	print_map(ctx.map);
	mlx_put_image_to_window(ctx.mlx, ctx.win, ctx.img.img, 0, 0);
	// mlx_hook(params.win, 2, 1L<<0, window_close, &params);
	// mlx_string_put(params.mlx, params.win, 0, 0, 0xFFFFFF, "Hello World\n");
	mlx_hook(ctx.win, 4, 1L<<2, press_button, &ctx);
	mlx_hook(ctx.win, 5, 1L<<3, release_button, &ctx);
	mlx_hook(ctx.win, 6, 1L<<6, button_motion_hook, &ctx);

	// mlx_loop_hook(params.mlx, mlx_put_image_to_window, &params);
	mlx_loop_hook(ctx.mlx, display_hud, &ctx);
	mlx_loop(ctx.mlx);
}
