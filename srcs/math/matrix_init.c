/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:34:45 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/20 19:55:47 by tafujise         ###   ########.fr       */
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

void	mat_scale(t_mat4 *m_scale, t_ctx *ctx)
{
	t_mat4	m_scale_raw;
	t_mat4	m_to_center;
	t_mat4	m_from_center;

	mat_identity(&m_scale_raw);
	m_scale_raw.mat[0][0] = ctx->camera.zoom;
	m_scale_raw.mat[1][1] = ctx->camera.zoom;
	m_scale_raw.mat[2][2] = ctx->camera.zoom;
	mat_identity(&m_to_center);
	m_to_center.mat[0][3] -= (double)(ctx->map.width - 1) / 2.0;
	m_to_center.mat[2][3] -= (double)(ctx->map.height - 1) / 2.0;
	mat_identity(&m_from_center);
	m_from_center.mat[0][3] += (double)(ctx->map.width - 1) / 2.0;
	m_from_center.mat[2][3] += (double)(ctx->map.height - 1) / 2.0;
	mat4_mul_3(m_scale, &m_from_center, &m_scale_raw, &m_to_center);
}

void	mat_rotate_x(t_mat4 *m_rotate_x, t_ctx *ctx)
{
	mat_identity(m_rotate_x);
	m_rotate_x->mat[1][1] = cos(ctx->camera.rot_x);
	m_rotate_x->mat[1][2] = -sin(ctx->camera.rot_x);
	m_rotate_x->mat[2][1] = sin(ctx->camera.rot_x);
	m_rotate_x->mat[2][2] = cos(ctx->camera.rot_x);
}

void	mat_rotate_y(t_mat4 *m_rotate_y, t_ctx *ctx)
{
	mat_identity(m_rotate_y);
	m_rotate_y->mat[0][0] = cos(ctx->camera.rot_y);
	m_rotate_y->mat[0][2] = sin(ctx->camera.rot_y);
	m_rotate_y->mat[2][0] = -sin(ctx->camera.rot_y);
	m_rotate_y->mat[2][2] = cos(ctx->camera.rot_y);
}

void	mat_rotate(t_mat4 *m_rotate, t_ctx *ctx)
{
	t_mat4	m_rotate_x;
	t_mat4	m_rotate_y;
	t_mat4	m_rotate_raw;
	t_mat4	m_to_center;
	t_mat4	m_from_center;

	mat_rotate_x(&m_rotate_x, ctx);
	mat_rotate_y(&m_rotate_y, ctx);
	mat4_mul(&m_rotate_raw, &m_rotate_y, &m_rotate_x);
	mat_identity(&m_to_center);
	m_to_center.mat[0][3] -= (double)(ctx->map.width - 1) / 2.0;
	m_to_center.mat[2][3] -= (double)(ctx->map.height - 1) / 2.0;
	mat_identity(&m_from_center);
	m_from_center.mat[0][3] += (double)(ctx->map.width - 1) / 2.0;
	m_from_center.mat[2][3] += (double)(ctx->map.height - 1) / 2.0;
	mat4_mul_3(m_rotate, &m_from_center, &m_rotate_raw, &m_to_center);
}

void	mat_translate(t_mat4 *m_translate, t_ctx *ctx)
{
	mat_identity(m_translate);
	m_translate->mat[0][3] = WIDTH / 2.0 + ctx->camera.offset_x;
	m_translate->mat[1][3] = HEIGHT / 2.0 + ctx->camera.offset_y;
}

