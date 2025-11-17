/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:33:01 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/17 22:51:14 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_ctx(t_ctx *ctx)
{
	if (ctx->map.points != NULL)
		free(ctx->map.points);
	if (ctx->mlx != NULL && ctx->img.img != NULL)
		mlx_destroy_image(ctx->mlx, ctx->img.img);
	if (ctx->mlx != NULL && ctx->win != NULL)
		mlx_destroy_window(ctx->mlx, ctx->win);
	if (ctx->mlx != NULL)
	{
		mlx_destroy_display(ctx->mlx);
		free(ctx->mlx);
	}
}