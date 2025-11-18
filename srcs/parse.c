/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 01:08:47 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/18 22:02:41 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_map_size(t_ctx *ctx, int fd);
static int	get_line_and_arr(char **line, char ***points, int fd);
static int	get_map_points(t_ctx *ctx, int fd);
static int	get_x_and_z(t_ctx *ctx, char **arr);
// static unsigned int	hexa_index(char c);
// static int	read_color(char *color, t_ctx *ctx);

int	parse_map(t_ctx *ctx, char *file_path)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (perror("open"), ERROR);
	if (get_map_size(ctx, fd) == ERROR)
		return (ERROR);
	ctx->map.points = malloc((ctx->map.width * ctx->map.height) 
						* sizeof(t_mappoint));
	if (!ctx->map.points)
		return (perror("malloc"), ERROR);
	close(fd);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (perror("open"), ERROR);
	if (get_map_points(ctx, fd) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	get_map_size(t_ctx *ctx, int fd)
{
	int	width;
	int	height;
	char	*line;
	char	**arr;

	width = 0;
	height = 0;
	if (get_line_and_arr(&line, &arr, fd) == ERROR)
		return (perror("read/malloc"), ERROR);
	width = ft_arrlen(arr);
	while (line != NULL && arr != NULL)
	{
		if (width != ft_arrlen(arr))
			return (ft_putstr_fd("Error: found wrong line\n", 1), ERROR);
		height++;
		if (get_line_and_arr(&line, &arr, fd) == ERROR)
			break;
	}
	ctx->map.width = width;
	ctx->map.height = height;
	printf("width: %d\n", ctx->map.width);
	printf("height: %d\n", ctx->map.height);
	return (SUCCESS);
}

static int	get_line_and_arr(char **line, char ***arr, int fd)
{
	*line = get_next_line(fd);
	if (*line == NULL || **line == '\0')
		return (ERROR);
	*arr = ft_split(*line, ' ');
	if (*arr == NULL)
		return (ERROR);
	return (SUCCESS);
}

static int	get_map_points(t_ctx *ctx, int fd)
{
	char	*line;
	char	**arr;
	int		y;

	y = 0;
	line = NULL;
	arr = NULL;
	if (get_line_and_arr(line, arr, fd) == ERROR)
		return (perror("read/malloc"), ERROR);
	while (line != NULL)
	{
		ctx->map.points->y = (double)y;
		if (get_x_and_z(ctx, arr) == ERROR)
			return (ERROR);
		if (get_line_and_arr(line, arr, fd) == ERROR)
			break;
		y++;
	}
	return (SUCCESS);
}

/*以下色の取得関連でSVG発生*/
int	get_x_and_z(t_ctx *ctx, char **arr)
{
	int	x;
	// char	**z_and_color;

	x = 0;
	while (arr[x] != NULL)
	{
		ctx->map.points->x = (double)x;
		// z_and_color = ft_split(arr[x], ',');
		// if (!z_and_color)
		// 	return (perror("malloc"), ERROR);
		// if (ft_arrlen(z_and_color) == 1)
		ctx->map.points->z = ft_atoi(arr[x]);
		// else
		// {
		// 	ctx->map.points->z = ft_atoi(z_and_color[0]);
		// 	if (read_color(z_and_color[1], ctx) == ERROR)
		// 		return (ERROR);
		// }
		x++;
	}
	return (SUCCESS);
}

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
