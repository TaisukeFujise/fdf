/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 08:53:16 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/15 23:11:18 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080
# include <mlx.h>
# include "../libft/libft.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

// typedef struct s_click
// {
// 	int	is_pressed;
// 	int	last_x;
// 	int	last_y;
// }	t_click;

// typedef struct s_hud
// {
// 	char	*zoom;
// 	char	*rotation;
// 	char	*translation;
// 	char	*projection_mode;
// 	char	*help;
// 	char	*color;
// }	t_hud;

typedef struct s_params
{
	void	*mlx;
	void	*win;
	t_data	*data;
	int	is_pressed;
	int	last_x;
	int	last_y;
	// t_hud	*hud;
}	t_params;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dst;

	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

#endif
