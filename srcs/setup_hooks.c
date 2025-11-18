/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 23:21:37 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/18 23:55:30 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	setup_hooks(t_ctx *ctx)
{
	mlx_hook(ctx->win, 4, 1L<<2, press_button, ctx);
	mlx_hook(ctx->win, 5, 1L<<3, release_button, ctx);
	mlx_hook(ctx->win, 6, 1L<<6, button_motion_hook, ctx);
	mlx_hook(ctx->win, 17, 1L<<17, window_close, ctx);
	mlx_hook(ctx->win, 2, 1L<<0, esc_close, ctx);
	// mlx_loop_hook(ctx->mlx, mlx_put_image_to_window, ctx);
	mlx_loop_hook(ctx->mlx, display_hud, ctx);
}
