/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:33:01 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 04:44:43 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_ctx(t_ctx *ctx)
{
	if (ctx->z_buf != NULL)
		free(ctx->z_buf);
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

void	free_row_and_cols(char **row_line, char ***cols)
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
	if (*row_line != NULL)
	{
		free(*row_line);
		*row_line = NULL;
	}
}

void	free_split(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
