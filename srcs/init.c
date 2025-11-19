/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:18:23 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/19 19:59:10 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	env_init(t_ctx *ctx)
{
	ctx->mlx = mlx_init();
	if (!ctx->mlx)
		return (perror("mlx"), ERROR);
	ctx->win = mlx_new_window(ctx->mlx, WIDTH, HEIGHT, "fdf");
	if (!ctx->win)
		return (perror("mlx window"), ERROR);
	ctx->img.img = mlx_new_image(ctx->mlx, WIDTH, HEIGHT);
	if (!ctx->img.img)
		return (perror("mlx img"), ERROR);
	ctx->img.addr = mlx_get_data_addr(ctx->img.img, &ctx->img.bits_per_pixel, &ctx->img.line_length, &ctx->img.endian);
	if (!ctx->img.addr)
		return (perror("mlx img addr"), ERROR);
	return (SUCCESS);
}

static void	camera_init(t_ctx *ctx)
{
	ctx->camera.zoom.ratio = 20.0;
	ctx->camera.zoom.lock = 1;
	ctx->camera.zoom.cursor_x = WIDTH / 2;
	ctx->camera.zoom.cursor_y = HEIGHT / 2;
	ctx->camera.mode = ISO;
	ctx->camera.rot_x = 35.264;
	ctx->camera.rot_y = 45;
}

int	ctx_init(t_ctx *ctx)
{
	ft_bzero(ctx, sizeof(t_ctx));
	if(env_init(ctx) == ERROR)
		return (ERROR);
	camera_init(ctx);
	return (SUCCESS);
}
