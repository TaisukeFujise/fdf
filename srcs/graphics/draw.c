/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:25:26 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 22:18:19 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	init_draw_param(t_draw_param *param, t_mappoint dot_0, t_mappoint dot_1)
{
	ft_bzero(param, sizeof(t_draw_param));
	param->x = (int)dot_0.screen_x;
	param->y = (int)dot_0.screen_y;
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
	param->z_curr = 0;
}

void	draw_line(t_ctx *ctx, t_mappoint dot_0, t_mappoint dot_1)
{
	t_draw_param	param;

	init_draw_param(&param, dot_0, dot_1);
	if (param.dx > param.dy)
	{
		draw_line_dx_base(ctx, &param, dot_0, dot_1);
	}
	else
	{
		draw_line_dy_base(ctx, &param, dot_0, dot_1);
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
	mlx_string_put(ctx->mlx, ctx->win, 30, 30, 0xFFFFFF, "== FDF ==");
	mlx_string_put(ctx->mlx, ctx->win, 30, 50, 0xFFFFFF, "Projection mode : ");
	mlx_string_put(ctx->mlx, ctx->win, 150, 50, 0xFFFFFF, mode);
	mlx_string_put(ctx->mlx, ctx->win, 30, 70, 0xFFFFFF, "Zoom : ");
	zoom = ft_itoa((int)ctx->camera.zoom);
	if (!zoom)
		return (ERROR);
	mlx_string_put(ctx->mlx, ctx->win, 80, 70, 0xFFFFFF, zoom);
	free(zoom);
	mlx_string_put(ctx->mlx, ctx->win, 30, 90, 0xFFFFFF, "Auto : press a");
	mlx_string_put(ctx->mlx, ctx->win, 30, 110, 0xFFFFFF, "Reset : press r");
	mlx_string_put(ctx->mlx, ctx->win, 30, 130, 0xFFFFFF, "Mode : press space");
	mlx_string_put(ctx->mlx, ctx->win, 30, 150, 0xFFFFFF, "ESC : press esc");
	return (SUCCESS);
}
