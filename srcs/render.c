/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:06:11 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/20 10:46:15 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	clear_image(t_ctx *ctx);
static int	update_map_projection(t_ctx *ctx);
static int	draw_wireframe(t_ctx *ctx);
void	draw_line(t_ctx *ctx, t_mappoint a, t_mappoint b);
static int	display_hud(t_ctx *ctx);
int	display_textbox(t_ctx *ctx);

int	render_next_frame(t_ctx *ctx)
{
	clear_image(ctx);
	update_map_projection(ctx);
	draw_wireframe(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img, 0, 0);
	display_hud(ctx);
	return (0);
}

static int	clear_image(t_ctx *ctx)
{
	if (ctx != NULL)
	{
		ft_bzero(ctx->img.addr, ctx->img.line_length * HEIGHT);
	}
	return (0);
}

/*
3次元座標 -> スクリーン2次元座標への変換 
(x, y, z) -> (screen_x, screen_y)
*/
static int	update_map_projection(t_ctx *ctx)
{
	t_mat4	m_model;

	build_model_matrix(&m_model, ctx);
	project_map(&m_model, ctx);
	print_map_spoint(ctx->map);
	return (0);
}

/*
スクリーン2次元座標を線分でimgの先頭アドレスimg.addrから、line_length * HEIGHTまで、
my_mlx_pixel_put(&img, i, j, color);で埋める。
*/
static int	draw_wireframe(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->map.width * ctx->map.height)
	{
		if (ctx->map.points[i].x + 1 < ctx->map.width)
			draw_line(ctx, ctx->map.points[i], ctx->map.points[i + 1]);
		if (ctx->map.points[i].y + 1 < ctx->map.height)
			draw_line(ctx, ctx->map.points[i], ctx->map.points[i + ctx->map.width]);
		i++;
	}
	return (0);
}

void	draw_line(t_ctx *ctx, t_mappoint a, t_mappoint b)
{
	// my_mlx_pixel_put(ctx, a.screen_x, a.screen_y, 0xFFFFFF);
	// my_mlx_pixel_put(ctx, b.screen_x, b.screen_y, 0xFFFFFF);
	(void)ctx;
	(void)a;
	(void)b;
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

static int	display_hud(t_ctx *ctx)
{
	char	*mode;
	char	*zoom;

	if (ctx->camera.mode == ISO)
		mode = "projection mode: isometric";
	else if (ctx->camera.mode == PAR)
		mode = "projection mode: parallel";
	else
		mode = "projection mode : conic";
	zoom = ft_strjoin("zoom : ", ft_itoa((int)ctx->camera.zoom.ratio));
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
