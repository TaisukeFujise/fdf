/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:25:26 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/20 19:55:27 by tafujise         ###   ########.fr       */
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

double	abs_double(double value)
{
	if (value < 0)
		return (value * (-1.0));
	return (value);
}

void	init_draw_param(t_draw_param *param, t_mappoint dot_0, t_mappoint dot_1)
{
	ft_bzero(param, sizeof(t_draw_param));
	param->dx = abs_double(dot_1.screen_x - dot_0.screen_x);
	param->dy = abs_double(dot_1.screen_y - dot_0.screen_y);
	if (dot_0.screen_x < dot_1.screen_x)
		param->sx = 1;
	else
		param->sx = -1;
	if (dot_0.screen_y < dot_1.screen_y)
		param->sy = 1;
	else
		param->sy = -1;
	param->err = 0;
}

void	draw_line(t_ctx *ctx, t_mappoint dot_0, t_mappoint dot_1)
{
	int	x;
	int	y;
	t_draw_param	param;

	x = (int)dot_0.screen_x;
	y = (int)dot_0.screen_y;
	init_draw_param(&param, dot_0, dot_1);
	if (param.dx > param.dy)
	{
		while (x != (int)dot_1.screen_x)
		{
			my_mlx_pixel_put(ctx, x, y, 0xFFFFFF);
			x += param.sx;
			param.err += param.dy / param.dx;
			if (param.err >= 0.5)
			{
				y += param.sy;
				param.err -= 1.0;
			}
		}
	}
	else
	{
		while (y != (int)dot_1.screen_y)
		{
			my_mlx_pixel_put(ctx, x, y, 0xFFFFFF);
			y += param.sy;
			param.err += param.dx / param.dy;
			if (param.err >= 0.5)
			{
				x += param.sx;
				param.err -= 1.0;
			}
		}
	}
}

int	display_hud(t_ctx *ctx)
{
	char	*mode;
	char	*zoom;

	if (ctx->camera.mode == ISO)
		mode = "projection mode : isometric";
	else if (ctx->camera.mode == PAR)
		mode = "projection mode : parallel";
	else
		mode = "projection mode : conic";
	zoom = ft_strjoin("zoom : ", ft_itoa((int)ctx->camera.zoom));
	if (zoom == NULL)
		return (1);
	display_textbox(ctx);
	mlx_string_put(ctx->mlx, ctx->win, 30, 30, 0xFFFFFF, "==Parameters==");
	mlx_string_put(ctx->mlx, ctx->win, 30, 50, 0xFFFFFF, mode);
	mlx_string_put(ctx->mlx, ctx->win, 30, 70, 0xFFFFFF, zoom);
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

