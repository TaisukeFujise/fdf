/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:40:54 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 15:57:15 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	build_model_matrix(t_mat4 *m_model, t_ctx *ctx)
{
	t_mat4	m_scale;
	t_mat4	m_rotate;
	t_mat4	m_translate;

	mat_scale(&m_scale, ctx);
	mat_rotate(&m_rotate, ctx);
	mat_translate(&m_translate, ctx);
	mat4_mul_3(m_model, &m_translate, &m_rotate, &m_scale);
}

void	model_to_screen(t_mat4 *m_model, t_mappoint *point)
{
	t_vec4	v_in;
	t_vec4	v_out;

	v_in.vec[0][0] = point->x;
	v_in.vec[1][0] = point->y;
	v_in.vec[2][0] = point->z;
	v_in.vec[3][0] = 1;
	mat_mul_vec4(m_model, &v_in, &v_out);
	point->screen_x = v_out.vec[0][0];
	point->screen_y = v_out.vec[1][0];
	point->screen_z = v_out.vec[2][0];
}

void	project_map(t_mat4 *m_model, t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < (ctx->map.width * ctx->map.height))
	{
		model_to_screen(m_model, &(ctx->map.points[i]));
		i++;
	}
}
