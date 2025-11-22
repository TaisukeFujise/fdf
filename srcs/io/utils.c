/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:52:53 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/22 20:14:05 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	count_cols_len(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL || *arr == NULL)
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
		return (value * (-1.0));
	return (value);
}

int	check_file_path(char *file_path)
{
	int	len;

	len = ft_strlen(file_path);
	if (len < 4)
		return (ERROR);
	if (ft_strcmp(&file_path[len - 4], ".fdf") != 0)
		return (ERROR);
	return (SUCCESS);
}

void	init_width_and_height(int *width, int *height)
{
	if (width == NULL || height == NULL)
		return ;
	*width = 0;
	*height = 0;
}
