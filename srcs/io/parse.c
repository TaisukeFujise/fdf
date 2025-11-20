/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 01:08:47 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 02:23:24 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	parse_map_size(t_ctx *ctx, int fd);
static int	read_and_split_line(char **row_line, char ***cols, int fd);
static int	parse_map_points(t_ctx *ctx, int fd);
static int	parse_height_color(t_mappoint *point, char *col);
int	hexa_index(char c);
int	check_hex_prefix(char **str);
uint32_t	ft_atoui32_hex(char *str);

int	parse_map(t_ctx *ctx, char *file_path)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (perror("open"), ERROR);
	if (parse_map_size(ctx, fd) == ERROR)
		return (ERROR);
	close(fd);

	ctx->map.points = malloc((ctx->map.width * ctx->map.height) 
						* sizeof(t_mappoint));
	if (!ctx->map.points)
		return (perror("malloc"), ERROR);

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (perror("open"), ERROR);
	if (parse_map_points(ctx, fd) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	read_and_split_line(char **row_line, char ***cols, int fd)
{
	*row_line = get_next_line(fd);
	if (*row_line == NULL || **row_line == '\0')
		return (ERROR);
	*cols = ft_split(*row_line, ' ');
	if (*cols == NULL)
		return (ERROR);
	return (SUCCESS);
}

static int	parse_map_size(t_ctx *ctx, int fd)
{
	int	width;
	int	height;
	char	*row_line;
	char	**cols;

	width = 0;
	height = 0;
	if (read_and_split_line(&row_line, &cols, fd) == ERROR)
		return (perror("read/malloc"),
				free_row_and_cols(&row_line, &cols), ERROR);
	width = count_cols_len(cols);
	while (row_line != NULL && cols != NULL)
	{
		if (width != count_cols_len(cols))
			return (ft_putstr_fd("Error: found wrong row_line\n", 1),
					free_row_and_cols(&row_line, &cols), ERROR);
		height++;
		if (read_and_split_line(&row_line, &cols, fd) == ERROR)
			break;
	}
	ctx->map.width = width;
	ctx->map.height = height;
	return (free_row_and_cols(&row_line, &cols), SUCCESS);
}

static int	parse_map_points(t_ctx *ctx, int fd)
{
	char	*row_line;
	char	**cols;
	int		col;
	int		row;
	int		i;

	if (read_and_split_line(&row_line, &cols, fd) == ERROR)
		return (perror("Error"), free_row_and_cols(&row_line, &cols), ERROR);
	row = 0;
	i = 0;
	while (row < ctx->map.height && row_line != NULL)
	{
		col = 0;
		while (col < ctx->map.width && cols != NULL)
		{
			ctx->map.points[i].x = (double)col;
			ctx->map.points[i].z = (double)row;
			parse_height_color(&ctx->map.points[i], cols[col]);
			i++;
			col++;
		}
		row++;
		if (read_and_split_line(&row_line, &cols, fd) == ERROR)
			break;
	}
	return (SUCCESS);
}

static int	parse_height_color(t_mappoint *point, char *col)
{
	char	**height_color;
	char	*height;
	char	*color;

	height_color = ft_split(col, ',');
	if (height_color == NULL)
		return (ft_putstr_fd("1Wrong value\n", 1), ERROR);
	height = *height_color;
	point->y = (double)((-1) * ft_atoi(height));
	height_color++;
	if (height_color == NULL)
		point->color = 0xFFFFFF;
	else
	{
		color = *height_color;
		point->color = ft_atoui32_hex(color);
	}
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

/*以下色の取得関連でSVG発生*/
// int	read_color(char *color, t_ctx *ctx)
// {
// 	unsigned int	num;
// 	unsigned int	index;

// 	if (ft_strlen(color) != 8 || color[0] != '0' || color[1] != 'x')
// 		return (ft_putstr_fd("Error: wrong color\n", 1), ERROR);
// 	color+= 2;
// 	while (*color)
// 	{
// 		index = hexa_index(*color);
// 		if ((int)index == -1)
// 			return (ft_putstr_fd("Error: wrong color\n", 1), ERROR);
// 		num = num * 16 + index;
// 		color++;
// 	}
// 	ctx->map.points->color = (uint32_t)num;
// 	return (SUCCESS);
// }
