/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 02:28:00 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/18 22:04:14 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
int	ft_arrlen(char **arr)
{
	int	i;
	
	i = 0;
	if (arr == NULL)
		return (i);
	while (arr[i] != NULL && ft_strcmp(arr[i], "\n") != 0)
	{
		// printf("arr: %s\n", arr[i]);
		i++;
	}
	return (i);
}
