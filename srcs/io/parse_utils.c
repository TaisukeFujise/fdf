/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 04:18:43 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 04:23:23 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	read_and_split_line(char **row_line, char ***cols, int fd)
{
	*row_line = get_next_line(fd);
	if (*row_line == NULL || **row_line == '\0')
		return (get_next_line(-1), ERROR);
	*cols = ft_split(*row_line, ' ');
	if (*cols == NULL)
		return (get_next_line(-1), ERROR);
	return (SUCCESS);
}

int	hexa_index(char c)
{
	char			*hexa_str_b;
	char			*hexa_str_s;
	unsigned int	index;

	hexa_str_b = "0123456789ABCDEF";
	hexa_str_s = "0123456789abcdef";
	index = 0;
	while (index < 16)
	{
		if (c == hexa_str_b[index] || c == hexa_str_s[index])
			return (index);
		index++;
	}
	return (-1);
}

int	check_hex_prefix(char **str)
{
	int	i;

	i = 0;
	if (*str == NULL)
		return (ERROR);
	if (ft_strlen(*str) < 3
		|| (*str)[i] != '0'
		|| (*str)[i + 1] != 'x')
		return (ERROR);
	(*str) += 2;
	return (SUCCESS);
}

uint32_t	ft_atoui32_hex(char *str)
{
	uint64_t	num;

	if (check_hex_prefix(&str) == ERROR)
		return (-1);
	num = (uint64_t)hexa_index(*str);
	if (num == (uint64_t)(-1))
		return (-1);
	str++;
	while (hexa_index(*str) != -1)
	{
		num = num * 16 + hexa_index(*str);
		str++;
	}
	return ((uint32_t)num);
}
