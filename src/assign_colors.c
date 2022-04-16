/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:07:44 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/16 16:08:00 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	assign_point_color(t_fdf_cont *cont, int x, int y)
{
	double	curr_alt;
	double	median_max;
	double	median_min;
	int		curr_color;

	curr_alt = cont->map[x + y * cont->map_w].z;
	median_max = cont->max_alt / 2;
	median_min = cont->min_alt / 2;
	curr_color = YELLOW;
	if (curr_alt > 0)
	{
		curr_color = average_color(YELLOW, RED, curr_alt / median_max);
		if (curr_alt > median_max)
			curr_color = average_color(RED, PINK, \
				linear_interpolation(median_max, cont->max_alt, curr_alt));
	}
	else if (curr_alt < 0)
	{
		curr_color = average_color(YELLOW, BLUE, curr_alt / median_min);
		if (curr_alt < median_min)
			curr_color = average_color(BLUE, CYAN, \
				linear_interpolation(median_min, cont->min_alt, curr_alt));
	}
	cont->map[x + y * cont->map_w].color = curr_color;
}

/* If z is negative, go from 0xFFFFFF to 0x00FFFF to 0x0000FF
 * If z is positive, go from 0xFFFFFF to 0xFFFF00 to 0xFF00FF
 */
void	assign_colors(t_fdf_cont *cont)
{
	int		x;
	int		y;

	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			assign_point_color(cont, x, y);
			x++;
		}
		y++;
	}
}
