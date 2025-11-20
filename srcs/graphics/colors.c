/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 22:03:00 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/20 22:07:14 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"


int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned char	get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}

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

