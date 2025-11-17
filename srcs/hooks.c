/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:41:58 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/18 00:17:37 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*hookの終了時には、free_ctxとexit(0)*/

int	window_close(int keycode, t_ctx *ctx)
{
	if (keycode == 65307)
		mlx_destroy_window(ctx->mlx, ctx->win);
	// if ()
	return (0);
}

// int	key_hook(int keycode, t_params *params)
// {
// 	(void)params;
// 	printf("key hook: %d\n", keycode);
// 	return (0);
// }

int	press_button(int button, int x, int y, t_ctx *ctx)
{
	(void)button;
	ctx->click.is_pressed = 1;
	ctx->click.last_x = x;
	ctx->click.last_y = y;
	return (0);
}

int	release_button(int button, int x, int y, t_ctx *ctx)
{
	(void)button;
	(void)x;
	(void)y;
	ctx->click.is_pressed = 0;
	return (0);
}

int	button_motion_hook(int x, int y, t_ctx *ctx)
{
	if (ctx->click.is_pressed == 1)
	{
		printf("===motion===\n");
		printf("button position: (%d, %d)\n", x, y);
	}
	return (0);
}

int	display_hud(t_ctx *ctx)
{
	mlx_string_put(ctx->mlx, ctx->win, 100, 70, 0xFFFFFF, "projection mode:");
	// mlx_string_put(ctx->mlx, ctx->win, 0, 0, 0xFFFFFF, params->hud->projection_mode);
	return (0);
}