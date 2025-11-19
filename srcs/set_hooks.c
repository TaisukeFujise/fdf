/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 23:21:37 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/19 18:48:46 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_hooks(t_ctx *ctx)
{
	mlx_hook(ctx->win, 2, 1L<<0, key_press, ctx);
	mlx_hook(ctx->win, 4, 1L<<2, button_press, ctx);
	mlx_hook(ctx->win, 5, 1L<<3, button_release, ctx);
	mlx_hook(ctx->win, 6, 1L<<6, button_motion, ctx);
	mlx_hook(ctx->win, 17, 1L<<17, window_close, ctx);
	mlx_loop_hook(ctx->mlx, render_next_frame, ctx);
}
