/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 01:08:47 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/19 16:57:56 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	parse_map_size(t_ctx *ctx, int fd);
static int	read_and_split_line(char **row_line, char ***cols, int fd);
static int	parse_map_points(t_ctx *ctx, int fd);
// static unsigned int	hexa_index(char c);
// static int	read_color(char *color, t_ctx *ctx);

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
			ctx->map.points[i].y = (double)ft_atoi(cols[col]);
			i++;
			col++;
		}
		row++;
	}
	return (SUCCESS);
}

/*以下色の取得関連でSVG発生*/


// unsigned int	hexa_index(char c)
// {
// 	char			*hexa_str;
// 	unsigned int	index;

// 	hexa_str = "0123456789ABCDEF";
// 	index = 0;
// 	while (hexa_str[index])
// 	{
// 		if (c == hexa_str[index])
// 			return (index);
// 		index++;
// 	}
// 	return (-1);
// }

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
