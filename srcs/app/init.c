/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:18:23 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/20 18:32:08 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	_env_init(t_ctx *ctx);
static void	_camera_init(t_ctx *ctx);

int	ctx_init(t_ctx *ctx)
{
	ft_bzero(ctx, sizeof(t_ctx));
	if(_env_init(ctx) == ERROR)
		return (ERROR);
	_camera_init(ctx);
	return (SUCCESS);
}

static int	_env_init(t_ctx *ctx)
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

static void	_camera_init(t_ctx *ctx)
{
	ctx->camera.zoom.ratio = 10.0;
	ctx->camera.zoom.lock = 1;
	ctx->camera.zoom.cursor_x = WIDTH / 2;
	ctx->camera.zoom.cursor_y = HEIGHT / 2;
	ctx->camera.mode = ISO;
	ctx->camera.rot_x = -atan(1 / sqrt(2));
	ctx->camera.rot_y = -PI/4;
}


