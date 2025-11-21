/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:17:57 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 22:21:11 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	my_mlx_pixel_put(t_ctx *ctx, t_draw_param *param, int color)
{
	int		offset;
	char	*dst;
	int		index;

	if ((0 <= param->x && param->x < WIDTH)
		&& (0 <= param->y && param->y < HEIGHT))
	{
		index = param->y * WIDTH + param->x;
		if (ctx->z_buf[index] >= param->z_curr)
			return ;
		offset = param->y * ctx->img.line_length
			+ param->x * (ctx->img.bits_per_pixel / 8);
		dst = ctx->img.addr + offset;
		if (dst == NULL)
			return ;
		ctx->z_buf[index] = param->z_curr;
		*(unsigned int *)dst = color;
	}
}

void	draw_line_dx_base(t_ctx *ctx, t_draw_param *param,
		t_mappoint dot_0, t_mappoint dot_1)
{
	while (param->x != (int)dot_1.screen_x)
	{
		param->step += 1.0 / param->dx;
		param->z_curr = (1 - param->step) * dot_0.screen_z
			+ param->step * dot_1.screen_z;
		my_mlx_pixel_put(ctx, param,
			lerp_mix_color(dot_0.color, dot_1.color, param->step));
		param->x += param->sx;
		param->err += param->dy / param->dx;
		if (param->err >= 0.5)
		{
			param->y += param->sy;
			param->err -= 1.0;
		}
	}
}

void	draw_line_dy_base(t_ctx *ctx, t_draw_param *param,
		t_mappoint dot_0, t_mappoint dot_1)
{
	while (param->y != (int)dot_1.screen_y)
	{
		param->step += 1.0 / param->dy;
		param->z_curr = (1 - param->step) * dot_0.screen_z
			+ param->step * dot_1.screen_z;
		my_mlx_pixel_put(ctx, param,
			lerp_mix_color(dot_0.color, dot_1.color, param->step));
		param->y += param->sy;
		param->err += param->dx / param->dy;
		if (param->err >= 0.5)
		{
			param->x += param->sx;
			param->err -= 1.0;
		}
	}
}
