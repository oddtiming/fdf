/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:07:49 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/16 16:08:00 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project_point(t_fdf_cont *cont, t_angles *angles, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p2 = cont->map[x + y * cont->map_w];
	apply_matrix(cont, angles, &p2);
	if (x)
	{
		p1 = cont->map[x - 1 + y * cont->map_w];
		apply_matrix(cont, angles, &p1);
		draw_line(cont, p1, p2);
	}
	if (y)
	{
		p1 = cont->map[x + (y - 1) * cont->map_w];
		apply_matrix(cont, angles, &p1);
		draw_line(cont, p1, p2);
	}
}

static t_angles	calculate_angles(t_fdf_cont *cont)
{
	t_angles	angles;

	angles.sin_x = sin(cont->theta_x);
	angles.sin_y = sin(cont->theta_y);
	angles.sin_z = sin(cont->theta_z);
	angles.cos_x = cos(cont->theta_x);
	angles.cos_y = cos(cont->theta_y);
	angles.cos_z = cos(cont->theta_z);
	return (angles);
}

void	display_map(t_fdf_cont *cont)
{
	t_angles	angles;
	int			x;
	int			y;

	angles = calculate_angles(cont);
	draw_background(cont->img, GREY);
	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			project_point(cont, &angles, x, y);
			x++;
		}
		y++;
	}
	display_default(cont);
	return ;
}
