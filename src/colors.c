/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:07:46 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/16 16:08:00 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline int	get_r(int color)
{
	return ((color >> 16) & 0xFF);
}

static inline int	get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

static inline int	get_b(int color)
{
	return (color & 0xFF);
}

int	average_color(int color1, int color2, double percent)
{
	int	r;
	int	g;
	int	b;

	if (color1 == color2)
		return (color1);
	r = (get_r(color2) - get_r(color1)) * percent + get_r(color1);
	g = (get_g(color2) - get_g(color1)) * percent + get_g(color1);
	b = (get_b(color2) - get_b(color1)) * percent + get_b(color1);
	return ((r << 16) | (g << 8) | (b));
}
