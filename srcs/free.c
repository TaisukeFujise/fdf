/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:33:01 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/18 22:42:21 by tafujise         ###   ########.fr       */
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

void	free_raw_and_cols(char **raw_line, char ***cols)
{
	int	i;

	i = 0;
	if (*cols != NULL)
	{
		while ((*cols)[i] != NULL)
		{
			free((*cols)[i]);
			i++;
		}
		free(*cols);
		*cols = NULL;
	}
	if (*raw_line != NULL)
	{
		free(*raw_line);
		*raw_line = NULL;
	}
}
