/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:25:26 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 04:12:47 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	my_mlx_pixel_put(t_ctx *ctx, int *dot, double z_curr, int color)
{
	int		offset;
	char	*dst;
	int		index;

	if ((0 <= dot[0] && dot[0] < WIDTH) && (0 <= dot[1] && dot[1] < HEIGHT))
	{
		index = dot[1] * WIDTH + dot[0];
		if (ctx->z_buf[index] >= z_curr)
			return ;
		offset = dot[1] * ctx->img.line_length
			+ dot[0] * (ctx->img.bits_per_pixel / 8);
		dst = ctx->img.addr + offset;
		if (dst == NULL)
			return ;
		ctx->z_buf[index] = z_curr;
		*(unsigned int *)dst = color;
	}
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
	param->step = 0;
}

void	draw_line(t_ctx *ctx, t_mappoint dot_0, t_mappoint dot_1)
{
	int				dot[2];
	t_draw_param	param;
	double			z_curr;

	dot[0] = (int)dot_0.screen_x;
	dot[1] = (int)dot_0.screen_y;
	init_draw_param(&param, dot_0, dot_1);
	if (param.dx > param.dy)
	{
		while (dot[0] != (int)dot_1.screen_x)
		{
			param.step += 1.0 / param.dx;
			z_curr = (1 - param.step) * dot_0.screen_z
				+ param.step * dot_1.screen_z;
			my_mlx_pixel_put(ctx, dot, z_curr,
				lerp_mix_color(dot_0.color, dot_1.color, param.step));
			dot[0] += param.sx;
			param.err += param.dy / param.dx;
			if (param.err >= 0.5)
			{
				dot[1] += param.sy;
				param.err -= 1.0;
			}
		}
	}
	else
	{
		while (dot[1] != (int)dot_1.screen_y)
		{
			param.step += 1.0 / param.dy;
			z_curr = (1 - param.step) * dot_0.screen_z
				+ param.step * dot_1.screen_z;
			my_mlx_pixel_put(ctx, dot, z_curr,
				lerp_mix_color(dot_0.color, dot_1.color, param.step));
			dot[1] += param.sy;
			param.err += param.dx / param.dy;
			if (param.err >= 0.5)
			{
				dot[0] += param.sx;
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
		mode = "Isometric";
	else if (ctx->camera.mode == PAR)
		mode = "Parallel";
	else
		mode = "Conic";
	mlx_string_put(ctx->mlx, ctx->win, 30, 30, 0xFFFFFF, "==Parameters==");
	mlx_string_put(ctx->mlx, ctx->win, 30, 50, 0xFFFFFF, "Projection mode : ");
	mlx_string_put(ctx->mlx, ctx->win, 150, 50, 0xFFFFFF, mode);
	mlx_string_put(ctx->mlx, ctx->win, 30, 70, 0xFFFFFF, "Zoom : ");
	zoom = ft_itoa((int)ctx->camera.zoom);
	if (!zoom)
		return (ERROR);
	mlx_string_put(ctx->mlx, ctx->win, 160, 70, 0xFFFFFF, zoom);
	free(zoom);
	return (SUCCESS);
}
