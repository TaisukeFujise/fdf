/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 08:53:16 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/18 23:55:55 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define SUCCESS 0
# define ERROR -1

# define WIDTH 1920
# define HEIGHT 1080

# include <mlx.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef enum e_mode
{
	ISO,
	PAR,
	CON,
}	t_mode;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_click
{
	int	is_pressed;
	int	last_x;
	int	last_y;
}	t_click;

typedef struct s_mappoint
{
	double		x;
	double		y;
	double		z;
	uint32_t	color;
	double		screen_x;
	double		screen_y;
}	t_mappoint;

typedef struct s_map
{
	int			width;
	int			height;
	t_mappoint	*points;
}	t_map;

typedef struct s_camera
{
	double	zoom;

	double	offset_x;
	double	offset_y;
	double	offset_z;

	double	rot_x;
	double	rot_y;
	double	rot_z;

	t_mode	mode;
}	t_camera;

typedef struct s_ctx
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_click		click;
	t_map		map;
	t_camera	camera;
}	t_ctx;

/* utils.c */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		count_cols_len(char **arr);
/* init.c */
int	ctx_init(t_ctx *ctx);
/* free.c */
void	free_ctx(t_ctx *ctx);
void	free_raw_and_cols(char **raw_line, char ***cols);
/* parse.c */
int	parse_map(t_ctx *ctx, char *file_path);
/* hooks.c */
int	window_close(t_ctx *ctx);
int	esc_close(int keycode, t_ctx *ctx);
int	press_button(int button, int x, int y, t_ctx *ctx);
int	release_button(int button, int x, int y, t_ctx *ctx);
int	button_motion_hook(int x, int y, t_ctx *ctx);
int	display_hud(t_ctx *ctx);
/* setup_hooks.c */
void	setup_hooks(t_ctx *ctx);

#endif
