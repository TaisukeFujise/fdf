/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:25:26 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/20 15:27:22 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	my_mlx_pixel_put(t_ctx *ctx, int x, int y, int color)
{
	int		offset;
	char	*dst;

	if ((0 <= x && x < WIDTH) && (0 <= y && y < HEIGHT))
	{
		offset = y * ctx->img.line_length + x * (ctx->img.bits_per_pixel / 8);
		dst = ctx->img.addr + offset;
		if (dst == NULL)
			return ;
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_ctx *ctx, t_mappoint a, t_mappoint b)
{
	my_mlx_pixel_put(ctx, a.screen_x, a.screen_y, 0xFFFFFF);
	my_mlx_pixel_put(ctx, b.screen_x, b.screen_y, 0xFFFFFF);
	// (void)ctx;
	// (void)a;
	// (void)b;
	// int		dx;
	// int		dy;
	// int		sx;
	// int		sy;
	// int		err;
	// int		err2;

	// dx = ABS((int)(b.screen_x - a.screen_x));
	// dy = ABS((int)(b.screen_y - a.screen_y));
	// if (a.screen_x < b.screen_x)
	// 	sx = 1;
	// else
	// 	sx = -1;
	// if (a.screen_y < b.screen_y)
	// 	sy = 1;
	// else
	// 	sy = -1;
	// err = dx - dy;
	// while (a.screen_x != b.screen_x || a.screen_y != b.screen_y)
	// {
	// 	my_mlx_pixel_put(ctx, a.screen_x, a.screen_y, 0xFFFFFF);
	// 	err2 = err * 2;
	// 	if (err2 > -dy)
	// 	{
	// 		err = err - dy;
	// 		a.screen_x += sx;
	// 	}
	// 	if (err2 < dx)
	// 	{
	// 		err = err + dx;
	// 		a.screen_y += sy;
	// 	}
	// }
}

int	display_hud(t_ctx *ctx)
{
	char	*mode;
	char	*zoom;
	char	*lock;

	if (ctx->camera.mode == ISO)
		mode = "projection mode : isometric";
	else if (ctx->camera.mode == PAR)
		mode = "projection mode : parallel";
	else
		mode = "projection mode : conic";
	zoom = ft_strjoin("zoom : ", ft_itoa((int)ctx->camera.zoom.ratio));
	if (zoom == NULL)
		return (1);
	if (ctx->camera.zoom.lock == 1)
		lock = "zoom lock : lock";
	else
		lock = "zoom lock : unlock";
	display_textbox(ctx);
	mlx_string_put(ctx->mlx, ctx->win, 30, 30, 0xFFFFFF, "==Parameters==");
	mlx_string_put(ctx->mlx, ctx->win, 30, 50, 0xFFFFFF, mode);
	mlx_string_put(ctx->mlx, ctx->win, 30, 70, 0xFFFFFF, zoom);
	mlx_string_put(ctx->mlx, ctx->win, 30, 90, 0xFFFFFF, lock);
	return (0);
}

int	display_textbox(t_ctx *ctx)
{
	int	i;
	int	j;

	i = 10;
	while (i < 250)
	{
		j = 10;
		while (j < 100)
		{
			if (i == 10 || i == 249 || j == 10 || j == 99 )
				my_mlx_pixel_put(ctx, i, j, 0xF0F8FF);
			j++;
		}
		i++;
	}
	return (0);
}

