/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:41:58 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/20 18:21:40 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, t_ctx *ctx)
{
	t_mode	cur_mode;

	if (keycode == 65361)
		ctx->camera.offset_x -= 5;
	else if (keycode == 65362)
		ctx->camera.offset_y -= 5;
	else if (keycode == 65363)
		ctx->camera.offset_x += 5;
	else if (keycode == 65364)
		ctx->camera.offset_y += 5;
	if (keycode == 32)
	{
		cur_mode = ctx->camera.mode;
		if (cur_mode == CON)
			ctx->camera.mode = ISO;
		else
			ctx->camera.mode++;
	}
	if (keycode == 65307)
		return(window_close(ctx));
	return (0);
}

int	button_press(int button, int x, int y, t_ctx *ctx)
{
	if (button == 1)
	{
		ctx->click.is_pressed = 1;
		ctx->click.last_x = x;
		ctx->click.last_y = y;
	}
	// if (button == 2)
	// {
	// 	printf("change lock\n");
	// 	ctx->camera.zoom.lock *= -1;
	// }
	// if (ctx->camera.zoom.lock == -1)
	// {
	if (button == 4 || button == 5)
	{
		// ctx->camera.zoom.cursor_x = x;
		// ctx->camera.zoom.cursor_y = y;
		if (button == 4)
			ctx->camera.zoom.ratio *= 1.1;
		else
			ctx->camera.zoom.ratio *= 0.9;
	}
	// }
	return (0);
}

int	button_release(int button, int x, int y, t_ctx *ctx)
{
	(void)button;
	(void)x;
	(void)y;
	ctx->click.is_pressed = 0;
	return (0);
}

int	button_motion(int x, int y, t_ctx *ctx)
{
	int	dx;
	int	dy;
	double	sensitivity;

	sensitivity = 0.00005;
	if (ctx->click.is_pressed == 1)
	{
		dx = x - ctx->click.last_x;
		dy = y - ctx->click.last_y;
		ctx->camera.rot_x += (double)dy * sensitivity;
		ctx->camera.rot_y -= (double)dx * sensitivity;
		if (ctx->camera.mode == ISO)
			ctx->camera.mode = PAR;
	}
	return (0);
}

int	window_close(t_ctx *ctx)
{
	free_ctx(ctx);
	exit(0);
	return (0);
}

