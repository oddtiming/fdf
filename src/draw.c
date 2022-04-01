#include "fdf.h"

static void	set_line_struct_x_fct_of_y(t_line *line)
{
	line->independent_var = &(line->p1.y);
	line->dependent_var = &(line->p1.x);
	line->independent_max = line->p2.y;
	if (line->p2.y > line->p1.y)
		line->independent_step = 1;
	else
		line->independent_step = -1;
	if (line->p2.x > line->p1.x)
		line->dependent_step = 1;
	else
		line->dependent_step = -1;
	line->offset_increment = line->dx * 2;
	line->offset_decrement = line->dy * 2;
	line->offset = (line->dx * 2) - line->dy;
	return ;
}

static void	set_line_struct(t_line *line)
{
	line->dx = fabs(line->p1.x - line->p2.x);
	line->dy = fabs(line->p1.y - line->p2.y);
	if (line->dx >= line->dy)
	{
		line->independent_var = &(line->p1.x);
		line->dependent_var = &(line->p1.y);
		line->independent_max = line->p2.x;
		if (line->p2.x > line->p1.x)
			line->independent_step = 1;
		else
			line->independent_step = -1;
		if (line->p2.y > line->p1.y)
			line->dependent_step = 1;
		else
			line->dependent_step = -1;
		line->offset_increment = line->dy * 2;
		line->offset_decrement = line->dx * 2;
		line->offset = (line->dy * 2) - line->dx;
	}
	else
		set_line_struct_x_fct_of_y(line);
	return ;
}

void	adjust_bounds_again_wtf(t_fdf_cont *cont, t_line *line)
{
	if (line->p1.x >= 0 && line->p1.x <= cont->win_w && \
		line->p1.y >= 0 && line->p1.y <= cont->win_h && \
		line->p2.x >= 0 && line->p2.x <= cont->win_w && \
		line->p2.y >= 0 && line->p2.y <= cont->win_h)
		return ;
	line->p1.x = nearbyint(line->p1.x);
	line->p1.x = nearbyint(line->p1.x);
	line->p2.x = nearbyint(line->p2.x);
	line->p2.x = nearbyint(line->p2.x);
	line->p1.y = nearbyint(line->p1.y);
	line->p1.y = nearbyint(line->p1.y);
	line->p2.y = nearbyint(line->p2.y);
	line->p2.y = nearbyint(line->p2.y);
}

int	adjust_bounds(t_fdf_cont *cont, t_point *p1, t_point *p2)
{
	if ((p1->x >= 0 && p1->x <= cont->win_w && \
		p1->y >= 0 && p1->y <= cont->win_h) && \
		(p2->x >= 0 && p2->x <= cont->win_w && \
		p2->y >= 0 && p2->y <= cont->win_h))
		return (EXIT_SUCCESS);
	if (p1->x < 0)
	{
		p1->y += linear_interpolation(p1->x, p2->x, 0) * (p2->y - p1->y);
		p1->x = 0;
	}
	else if (p1->x > cont->win_w - 1)
	{
		p1->y += linear_interpolation(p1->x, p2->x, cont->win_w - 1) * (p2->y - p1->y);
		p1->x = cont->win_w - 1;
	}
	else if (p2->x < 0)
	{
		p2->y += linear_interpolation(p2->x, p1->x, 0) * (p1->y - p2->y);
		p2->x = 0;
	}
	else if (p2->x > cont->win_w - 1)
	{
		p2->y += linear_interpolation(p2->x, p1->x, cont->win_w - 1) * (p1->y - p2->y);
		p2->x = cont->win_w - 1;
	}
	if (p1->y < 0)
	{
		p1->x += linear_interpolation(p1->y, p2->y, 0) * (p2->x - p1->x);
		p1->y = 0;
	}
	else if (p1->y > cont->win_h - 1)
	{
		p1->x += linear_interpolation(p1->y, p2->y, cont->win_h - 1) * (p2->x - p1->x);
		p1->y = cont->win_h - 1;
	}
	else if (p2->y < 0)
	{
		p2->x += linear_interpolation(p2->y, p1->y, 0) * (p1->x - p2->x);
		p2->y = 0;
	}
	else if (p2->y > cont->win_h - 1)
	{
		p2->x += linear_interpolation(p2->y, p1->y, cont->win_h - 1) * (p1->x - p2->x);
		p2->y = cont->win_h - 1;
	}
	if ((p1->x < 0 || p1->x > cont->win_w - 1 || \
		p1->y < 0 || p1->y > cont->win_h - 1) || \
		(p2->x < 0 || p2->x > cont->win_w - 1 || \
		p2->y < 0 || p2->y > cont->win_h - 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	draw_line(t_fdf_cont *cont, t_point p1, t_point p2)
{
	t_line	*line;
	double	color_percent;
	int		pixel_color;

	line = ft_safealloc(sizeof(t_line));
	// if (adjust_bounds(cont, &p1, &p2))
	if ((!cont->toggle_proj && (p1.z <= 0 || p2.z <= 0)) || adjust_bounds(cont, &p1, &p2))
	{
		free(line);
		return ;
	}
	line->p1 = p1;
	line->p2 = p2;
	set_line_struct(line);
	while (*line->independent_var != line->independent_max && \
			*line->independent_var >= 0 && *line->independent_var < 1280 && \
			*line->dependent_var >= 0 && *line->dependent_var < 1280)
	{
		*line->independent_var = (int)(line->independent_step + *line->independent_var);
		if (line->offset >= 0)
		{
			*line->dependent_var = (int)(line->dependent_step + *line->dependent_var);
			line->offset -= line->offset_decrement;
		}
		line->offset += line->offset_increment;
		if (cont->map_is_colored)
		{
			if (line->dx >= line->dy)
				color_percent = linear_interpolation(p1.x, p2.x, line->p1.x);
			else
				color_percent = linear_interpolation(p1.y, p2.y, line->p1.y);
			pixel_color = average_color(p1.color, p2.color, color_percent);
		}
		else
			pixel_color = FDF_WHITE;
		fill_pixel(cont->img, line->p1.x, line->p1.y, pixel_color);
	}
	free(line);
	return ;
}

void	draw_line_rainbow(t_img *img, t_point p1, t_point p2)
{
	t_line	*line;
	int		color;

	line = ft_safealloc(sizeof(t_line));
	line->p1 = p1;
	line->p2 = p2;
	set_line_struct(line);
	color = 0x010101;
	fill_pixel(img, line->p1.x, line->p1.y, color);
	while (*line->independent_var != line->independent_max)
	{
		*line->independent_var += line->independent_step;
		if (line->offset >= 0)
		{
			*line->dependent_var += line->dependent_step;
			line->offset -= line->offset_decrement;
		}
		line->offset += line->offset_increment;
		change_color(line->p1.x, line->p1.y, &color);
		fill_pixel(img, line->p1.x, line->p1.y, color);
	}
	free(line);
	return ;
}

void	draw_line_rainbow_offset(t_img *img, t_point p1, t_point p2, int offset)
{
	t_line	*line;
	int		color;

	line = ft_safealloc(sizeof(t_line));
	line->p1 = p1;
	line->p2 = p2;
	set_line_struct(line);
	color = 0x010101;
	fill_pixel(img, line->p1.x, line->p1.y, color);
	while (*line->independent_var != line->independent_max)
	{
		*line->independent_var += line->independent_step;
		if (line->offset >= 0)
		{
			*line->dependent_var += line->dependent_step;
			line->offset -= line->offset_decrement;
		}
		line->offset += line->offset_increment;
		change_color_offset(line->p1.x, line->p1.y, &color, offset);
		fill_pixel(img, line->p1.x, line->p1.y, color);
	}
	free(line);
	return ;
}

void	draw_square_rainbow(t_img *img, int size)
{
	int	x;
	int	y;
	int	color;

	y = (img->height - size);
	color = FDF_WHITE;
	while (y <= (img->height + size))
	{
		x = (img->width - size);
		while (x <= (img->width + size))
		{
			change_color(x - (img->width - size), y - (img->height - size), &color);
			fill_pixel(img, x / 2, y / 2, color);
			x++;
		}
		y++;
	}
	return ;
}

//This only takes black and white as inputs
void	draw_background(t_img *img, int color)
{
	ft_memset(img->data_addr, color, img->line_len * img->height);
}
