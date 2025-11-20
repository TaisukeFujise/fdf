/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:33:46 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 04:00:14 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	mat_identity(t_mat4 *mat)
{
	ft_bzero(mat, sizeof(t_mat4));
	mat->mat[0][0] = 1;
	mat->mat[1][1] = 1;
	mat->mat[2][2] = 1;
	mat->mat[3][3] = 1;
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

void	mat4_mul_3(t_mat4 *dst, t_mat4 *mat_a, t_mat4 *mat_b, t_mat4 *mat_c)
{
	t_mat4	tmp;

	ft_bzero(dst, sizeof(t_mat4));
	mat4_mul(&tmp, mat_b, mat_c);
	mat4_mul(dst, mat_a, &tmp);
}
