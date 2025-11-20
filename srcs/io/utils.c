/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:52:53 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/20 14:29:32 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

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
