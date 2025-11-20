/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:18:23 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 02:52:10 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	_env_init(t_ctx *ctx);
static void	_camera_init(t_ctx *ctx);
static int	_z_buffer_init(t_ctx *ctx);

int	ctx_init(t_ctx *ctx)
{
	ft_bzero(ctx, sizeof(t_ctx));
	if(_env_init(ctx) == ERROR)
		return (ERROR);
	_camera_init(ctx);
	if (_z_buffer_init(ctx) == ERROR)
		return (ERROR);
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
	ctx->camera.zoom = 10.0;
	ctx->camera.mode = ISO;
	ctx->camera.rot_x = -atan(1 / sqrt(2));
	ctx->camera.rot_y = PI/4;
}

static int	_z_buffer_init(t_ctx *ctx)
{
	int	i;

	ctx->z_buf = malloc(sizeof(double) * WIDTH * HEIGHT);
	if (!ctx->z_buf)
		return (ERROR) ;
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		ctx->z_buf[i] = -DBL_MAX;
		i++;
	}
	return (SUCCESS);
}

void	scale_init(t_ctx *ctx)
{
	double	map_w;
	double	map_h;
	double	zoom;

	map_w = ctx->map.width;
	map_h = ctx->map.height;
	if (map_w > map_h)
		zoom = (WIDTH / map_w) * 0.4;
	else
		zoom = (HEIGHT / map_h) * 0.4;
	while (zoom < 0)
		zoom += 0.001;
	ctx->camera.zoom = zoom;
}
