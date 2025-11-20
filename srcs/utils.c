/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:52:53 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/20 10:32:25 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>


void	my_mlx_pixel_put(t_ctx *ctx, int x, int y, int color)
{
	int		offset;
	char	*dst;

	if ((0 <= x && x < WIDTH) || (0 <= y && y < HEIGHT))
	{
		offset = y * ctx->img.line_length + x * (ctx->img.bits_per_pixel / 8);
		dst = ctx->img.addr + offset;
		if (dst == NULL)
			return ;
		*(unsigned int *)dst = color;
	}
}

int	count_cols_len(char **arr)
{
	int	i;
	
	i = 0;
	if (arr == NULL)
		return (i);
	while (arr[i] != NULL && ft_strcmp(arr[i], "\n") != 0)
	{
		i++;
	}
	return (i);
}

double	abs_double(double value)
{
	if (value < 0)
		return (-value);
	return (value);
}
