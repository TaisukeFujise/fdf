/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 03:56:14 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 03:56:29 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

uint32_t	mix_color(uint32_t color1, uint32_t color2)
{
	unsigned char	new_t;
	unsigned char	new_r;
	unsigned char	new_g;
	unsigned char	new_b;

	new_t = (get_t(color1) + get_t(color2)) / 2;
	new_r = (get_r(color1) + get_r(color2)) / 2;
	new_g = (get_g(color1) + get_g(color2)) / 2;
	new_b = (get_b(color1) + get_b(color2)) / 2;
	return (create_trgb(new_t, new_r, new_g, new_b));
}

uint32_t	lerp_mix_color(uint32_t color1, uint32_t color2, double step)
{
	unsigned char	new_t;
	unsigned char	new_r;
	unsigned char	new_g;
	unsigned char	new_b;

	new_t = get_t(color1) * (1 - step) + get_t(color2) * step;
	new_r = get_r(color1) * (1 - step) + get_r(color2) * step;
	new_g = get_g(color1) * (1 - step) + get_g(color2) * step;
	new_b = get_b(color1) * (1 - step) + get_b(color2) * step;
	return (create_trgb(new_t, new_r, new_g, new_b));
}
