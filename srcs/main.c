/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 09:29:34 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/18 00:51:18 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

int	main(void)
{
	t_ctx	ctx;
	
	if (ctx_init(&ctx) == ERROR)
	{
		free_ctx(&ctx);
		return (1);
	};
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

// #include <stdio.h>

// int	key_press(int keycode, void *param)
// {
// 	(void)param;
// 	printf("keycode = %d\n", keycode);
// 	return (0);
// }

// int main(void)
// {
// 	void	*mlx = mlx_init();
// 	void	*win = mlx_new_window(mlx, 200, 200, "key test");
// 	mlx_hook(win, 2, 1L<<0, key_press, NULL);
// 	mlx_loop(mlx);
// }
