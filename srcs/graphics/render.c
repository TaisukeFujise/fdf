/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:06:11 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 03:57:12 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	_clear_image(t_ctx *ctx);
static int	_update_map_projection(t_ctx *ctx);
static int	_draw_wireframe(t_ctx *ctx);

int	render_next_frame(t_ctx *ctx)
{
	_clear_image(ctx);
	_update_map_projection(ctx);
	_draw_wireframe(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img, 0, 0);
	display_hud(ctx);
	return (0);
}

static int	_clear_image(t_ctx *ctx)
{
	int	i;

	if (ctx != NULL)
	{
		ft_bzero(ctx->img.addr, ctx->img.line_length * HEIGHT);
		i = 0;
		while (i < WIDTH * HEIGHT)
		{
			ctx->z_buf[i] = -DBL_MAX;
			i++;
		}
	}
	return (0);
}

static int	_update_map_projection(t_ctx *ctx)
{
	t_mat4	m_model;

	build_model_matrix(&m_model, ctx);
	project_map(&m_model, ctx);
	return (0);
}

static int	_draw_wireframe(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->map.width * ctx->map.height)
	{
		if (ctx->map.points[i].x + 1 < ctx->map.width)
		{
			draw_line(ctx, ctx->map.points[i], ctx->map.points[i + 1]);
		}
		if (ctx->map.points[i].z + 1 < ctx->map.height)
		{
			draw_line(ctx, ctx->map.points[i],
				ctx->map.points[i + ctx->map.width]);
		}
		i++;
	}
	return (0);
}
