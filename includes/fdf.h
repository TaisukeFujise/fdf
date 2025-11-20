/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 08:53:16 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/20 16:30:52 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define SUCCESS 0
# define ERROR -1

# define WIDTH 1920
# define HEIGHT 1080

# define PI 3.14159265358979323846

# define ABS(Value) (((Value) ^ ((Value) >> 31)) - ((Value) >> 31))

# include <mlx.h>
# include <fcntl.h>
# include <math.h>
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
	double		screen_z;
}	t_mappoint;

typedef struct s_map
{
	int			width;
	int			height;
	t_mappoint	*points;
}	t_map;

typedef struct s_zoom
{
	double	ratio;
	int		lock;
	int		cursor_x;
	int		cursor_y;
}	t_zoom;

typedef struct s_camera
{
	double	rot_x;
	double	rot_y;
	// double	rot_z;
	double	offset_x;
	double	offset_y;
	t_zoom	zoom;
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

typedef struct s_mat4
{
	double	mat[4][4];
}	t_mat4;

typedef struct s_vec4
{
	double	vec[4][1];
}	t_vec4;

/* <app>*/
/* init.c */
int	ctx_init(t_ctx *ctx);
/* free.c */
void	free_ctx(t_ctx *ctx);
void	free_row_and_cols(char **row_line, char ***cols);

/* <graphics> */
/* hooks.c */
int	key_press(int keycode, t_ctx *ctx);
int	button_press(int button, int x, int y, t_ctx *ctx);
int	button_release(int button, int x, int y, t_ctx *ctx);
int	button_motion(int x, int y, t_ctx *ctx);
int	window_close(t_ctx *ctx);
/* render.c */
int	render_next_frame(t_ctx *ctx);
/* draw.c */
void	my_mlx_pixel_put(t_ctx *ctx, int x, int y, int color);
void	draw_line(t_ctx *ctx, t_mappoint a, t_mappoint b);
int	display_hud(t_ctx *ctx);
int	display_textbox(t_ctx *ctx);
/* setup_hooks.c */
void	set_hooks(t_ctx *ctx);

/* <math> */
/* matrix_init.c */
void	mat_identity(t_mat4 *mat);
void	mat_scale(t_mat4 *m_scale, t_ctx *ctx);
// void	mat_zoom(t_mat4 *m_zoom, t_ctx *ctx);
void	mat_rotate(t_mat4 *m_rotate, t_ctx *ctx);
void	mat_translate(t_mat4 *m_translate, t_ctx *ctx);
// void	mat_t_r(t_mat4 *m_t_r, t_ctx *ctx);
/* matrix_utils.c */
void	mat_mul_vec4(t_mat4 *mat, t_vec4 *t_in, t_vec4 *t_out);
void	mat4_mul(t_mat4 *dst, t_mat4 *a, t_mat4 *b);
void	mat4_mul_3(t_mat4 *dst, t_mat4 *mat_a, t_mat4 *mat_b, t_mat4 *mat_c);
/* transform.c*/
void	build_model_matrix(t_mat4 *m_model, t_ctx *ctx);
void	project_map(t_mat4 *m_model, t_ctx *ctx);

/* <io> */
/* parse.c */
int	parse_map(t_ctx *ctx, char *file_path);
/* utils.c */
int		count_cols_len(char **arr);

/* <other> */
/* test.c */
void	print_mappoint(t_map map);
void	print_map_spoint(t_map map);
#endif
