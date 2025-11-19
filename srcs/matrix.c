/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:02:38 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/19 23:34:26 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	mat_identity(t_mat4 *mat)
{
	ft_bzero(mat, sizeof(t_mat4));
	mat->mat[0][0] = 1;
	mat->mat[1][1] = 1;
	mat->mat[2][2] = 1;
	mat->mat[3][3] = 1;
}

void	mat4_mul(t_mat4 *dst, t_mat4 *a, t_mat4 *b)
{
	int	i;
	int	j;
	int	k;

	ft_bzero(dst, sizeof(t_mat4));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				dst->mat[i][j] += a->mat[i][k] * b->mat[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}

void	mat_mul_vec4(t_mat4 *mat, t_vec4 *t_in, t_vec4 *t_out)
{
	int	i;
	int	j;

	ft_bzero(t_out, sizeof(t_vec4));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			t_out->vec[i][0] += mat->mat[i][j] * t_in->vec[j][0];
			j++;
		}
		i++;
	}
}

void	mat_scale(t_mat4 *m_scale, t_ctx *ctx)
{
	mat_identity(m_scale);
	m_scale->mat[0][0] = ctx->camera.zoom.ratio;
	m_scale->mat[1][1] = ctx->camera.zoom.ratio;
	m_scale->mat[2][2] = ctx->camera.zoom.ratio;
}

void	mat_zoom(t_mat4 *m_zoom, t_ctx *ctx)
{
	t_mat4	m_scale;
	t_mat4	m_to_cursor;
	t_mat4	m_from_cursor;
	t_mat4	m_temp;

	mat_identity(&m_scale);
	mat_scale(&m_scale, ctx);
	mat_identity(&m_to_cursor);
	mat_identity(&m_from_cursor);
	m_to_cursor.mat[0][3] = ctx->camera.zoom.cursor_x - WIDTH / 2;
	m_to_cursor.mat[1][3] = ctx->camera.zoom.cursor_y - HEIGHT / 2;
	m_from_cursor.mat[0][3] = -(ctx->camera.zoom.cursor_x - WIDTH / 2);
	m_to_cursor.mat[1][3] = -(ctx->camera.zoom.cursor_y - HEIGHT / 2);
	mat4_mul(&m_temp, &m_scale, &m_to_cursor);
	mat4_mul(m_zoom, &m_from_cursor, &m_temp);
}



void	mat_rotate(t_mat4 *m_rotate, t_ctx *ctx)
{
	t_mat4	m_rotate_x;
	t_mat4	m_rotate_y;

	mat_identity(m_rotate);
	mat_identity(&m_rotate_x);
	mat_identity(&m_rotate_y);
	m_rotate_x.mat[1][1] = cos(ctx->camera.rot_x);
	m_rotate_x.mat[1][2] = -sin(ctx->camera.rot_x);
	m_rotate_x.mat[2][1] = sin(ctx->camera.rot_x);
	m_rotate_x.mat[2][2] = cos(ctx->camera.rot_x);

	m_rotate_y.mat[0][0] = cos(ctx->camera.rot_y);
	m_rotate_y.mat[0][2] = sin(ctx->camera.rot_y);
	m_rotate_y.mat[2][0] = -sin(ctx->camera.rot_y);
	m_rotate_y.mat[2][2] = cos(ctx->camera.rot_y);
	mat4_mul(m_rotate, &m_rotate_x, &m_rotate_y);
}

void	mat_translate(t_mat4 *m_translate, t_ctx *ctx)
{
	mat_identity(m_translate);
	m_translate->mat[0][3] = WIDTH / 2 + ctx->camera.offset_x;
	m_translate->mat[1][3] = HEIGHT / 2 + ctx->camera.offset_y;
}


void	mat_t_r(t_mat4 *m_t_r, t_ctx *ctx)
{
	t_mat4	m_rotate;
	t_mat4	m_translate;

	mat_identity(&m_rotate);
	mat_rotate(&m_rotate, ctx);
	mat_identity(&m_translate);
	mat_translate(&m_translate, ctx);
	mat_identity(m_t_r);
	mat4_mul(m_t_r, &m_translate, &m_rotate);
}

