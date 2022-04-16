/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:07:36 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/16 16:08:00 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_line_struct_x_fct_of_y(t_bresenham *line)
{
	line->is_reverse = true;
	line->indep_var = &(line->p1.y);
	line->dep_var = &(line->p1.x);
	line->indep_max = line->p2.y;
	if (line->p2.y > line->p1.y)
		line->indep_step = 1;
	else
		line->indep_step = -1;
	if (line->p2.x > line->p1.x)
		line->dep_step = 1;
	else
		line->dep_step = -1;
	line->offset_increment = line->dx * 2;
	line->offset_decrement = line->dy * 2;
	line->offset = (line->dx * 2) - line->dy;
	return ;
}

static void	set_line_struct(t_bresenham *line)
{
	line->dx = fabs(line->p1.x - line->p2.x);
	line->dy = fabs(line->p1.y - line->p2.y);
	if (line->dx < line->dy)
	{
		set_line_struct_x_fct_of_y(line);
		return ;
	}
	line->is_reverse = false;
	line->indep_var = &(line->p1.x);
	line->dep_var = &(line->p1.y);
	line->indep_max = line->p2.x;
	if (line->p2.x > line->p1.x)
		line->indep_step = 1;
	else
		line->indep_step = -1;
	if (line->p2.y > line->p1.y)
		line->dep_step = 1;
	else
		line->dep_step = -1;
	line->offset_increment = line->dy * 2;
	line->offset_decrement = line->dx * 2;
	line->offset = (line->dy * 2) - line->dx;
	return ;
}

static void	bresenham(t_bresenham *line)
{
	*line->indep_var = (int)(line->indep_step + *line->indep_var);
	if (line->offset >= 0)
	{
		*line->dep_var = (int)(line->dep_step + *line->dep_var);
		line->offset -= line->offset_decrement;
	}
	line->offset += line->offset_increment;
}

static void	interpolate_color(t_fdf_cont *cont, t_bresenham *line,
		t_point *p1, t_point *p2)
{
	double	color_percent;
	int		pixel_color;

	if (cont->map_is_colored)
	{
		if (line->dx >= line->dy)
			color_percent = linear_interpolation(p1->x, p2->x, line->p1.x);
		else
			color_percent = linear_interpolation(p1->y, p2->y, line->p1.y);
		pixel_color = average_color(p1->color, p2->color, color_percent);
	}
	else
		pixel_color = WHITE;
	fill_pixel(cont->img, line->p1.x, line->p1.y, pixel_color);
}

void	draw_line(t_fdf_cont *cont, t_point p1, t_point p2)
{
	t_bresenham	*line;

	if (line_clipping(cont, &p1, &p2))
		return ;
	line = ft_safealloc(sizeof(t_bresenham));
	line->p1 = p1;
	line->p2 = p2;
	set_line_struct(line);
	while (*line->indep_var != line->indep_max && \
			*line->indep_var >= 0 && *line->indep_var < 1280 && \
			*line->dep_var >= 0 && *line->dep_var < 1280)
	{
		bresenham(line);
		interpolate_color(cont, line, &p1, &p2);
	}
	free(line);
	return ;
}
