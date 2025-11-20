/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 01:08:47 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 05:06:06 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	parse_map_size(t_ctx *ctx, int fd);
static int	parse_map_points(t_ctx *ctx, int fd);
static int	parse_height_color(t_mappoint *point, char *col);

int	parse_map(t_ctx *ctx, char *file_path)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (perror("open"), ERROR);
	if (parse_map_size(ctx, fd) == ERROR)
		return (close(fd), ERROR);
	close(fd);
	ctx->map.points = malloc((ctx->map.width * ctx->map.height)
			* sizeof(t_mappoint));
	if (!ctx->map.points)
		return (perror("malloc"), ERROR);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (perror("open"), ERROR);
	if (parse_map_points(ctx, fd) == ERROR)
		return (close(fd), ERROR);
	return (close(fd), SUCCESS);
}

static int	parse_map_size(t_ctx *ctx, int fd)
{
	int		width;
	int		height;
	char	*row_line;
	char	**cols;

	width = 0;
	height = 0;
	if (read_and_split_line(&row_line, &cols, fd) == ERROR)
		return (perror("read/malloc"), free_row_and_cols(&row_line, &cols), gnl_cleanup(), ERROR);
	width = count_cols_len(cols);
	while (row_line != NULL && cols != NULL)
	{
		if (width != count_cols_len(cols))
			return (ft_putstr_fd("Error: found wrong row_line\n", 1), free_row_and_cols(&row_line, &cols), gnl_cleanup(), ERROR);
		height++;
		free_row_and_cols(&row_line, &cols);
		if (read_and_split_line(&row_line, &cols, fd) == ERROR)
			break ;
	}
	ctx->map.width = width;
	ctx->map.height = height;
	return (free_row_and_cols(&row_line, &cols), gnl_cleanup(), SUCCESS);
}

static int	parse_map_points(t_ctx *ctx, int fd)
{
	char	*row_line;
	char	**cols;
	int		col;
	int		row;
	int		i;

	if (read_and_split_line(&row_line, &cols, fd) == ERROR)
		return (perror("Error"), free_row_and_cols(&row_line, &cols), gnl_cleanup(), ERROR);
	row = 0;
	i = 0;
	while (row < ctx->map.height && row_line != NULL)
	{
		col = 0;
		while (col < ctx->map.width && cols != NULL)
		{
			ctx->map.points[i].x = (double)col;
			ctx->map.points[i].z = (double)row;
			if (parse_height_color(&ctx->map.points[i], cols[col]) == ERROR)
				return (perror("Error"), free_row_and_cols(&row_line, &cols), gnl_cleanup(), ERROR);
			i++;
			col++;
		}
		row++;
		free_row_and_cols(&row_line, &cols);
		if (read_and_split_line(&row_line, &cols, fd) == ERROR)
			break ;
	}
	free_row_and_cols(&row_line, &cols);
	return (gnl_cleanup(), SUCCESS);
}

static int	parse_height_color(t_mappoint *point, char *col)
{
	char	**height_color;
	char	*height;
	char	*color;

	height_color = ft_split(col, ',');
	if (height_color == NULL)
		return (ft_putstr_fd("1Wrong value\n", 1), ERROR);
	height = height_color[0];
	point->y = (double)((-1) * ft_atoi(height));
	if (height_color[1] == NULL)
		color = "0xFFFFFF";
	else
		color = height_color[1];
	point->color = ft_atoui32_hex(color);
	free_split(height_color);
	return (SUCCESS);
}
