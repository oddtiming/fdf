#include "fdf.h"

void	invert_line_points(t_line *line)
{
	int	temp_x;
	int	temp_y;

	temp_x = line->p1.x;
	temp_y = line->p1.y;
	line->p1.x = line->p2.x;
	line->p1.y = line->p2.y;
	line->p2.x = temp_x;
	line->p2.y = temp_y;
	return ;
}

void	set_line_struct(t_line *line)
{
	line->dx = abs(line->p1.x - line->p2.x);
	line->dy = abs(line->p1.y - line->p2.y);
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
		line->offset_increment = line->dy << 1;
		line->offset_decrement = line->dx << 1;
		line->offset = (line->dy << 1) - line->dx;
	}
	else
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
		line->offset_increment = line->dx << 1;
		line->offset_decrement = line->dy << 1;
		line->offset = (line->dx << 1) - line->dy;
	}
	return ;
}

void	draw_line(t_img *img, t_2d_point p1, t_2d_point p2)
{
	t_line	*line;

	line = ft_safealloc(sizeof(t_line));
	line->p1 = p1;
	line->p2 = p2;
	set_line_struct(line);
	fill_pixel(img, line->p1.x, line->p1.y, FDF_WHITE);
	while (*line->independent_var != line->independent_max)
	{
		*line->independent_var += line->independent_step;
		if (line->offset >= 0)
		{
			*line->dependent_var += line->dependent_step;
			line->offset -= line->offset_decrement;
		}
		line->offset += line->offset_increment;
		fill_pixel(img, line->p1.x, line->p1.y, FDF_WHITE);
	}
	free(line);
	return ;
}

void	draw_square(t_img *img, int size)
{
	int	x;
	int	y;

	y = (img->height - size) / 2;
	while (y <= (img->height + size) / 2)
	{
		x = (img->width - size) / 2;
		while (x <= (img->width + size) / 2)
		{
			fill_pixel(img, x, y, FDF_CYAN);
			x++;
		}
		y++;
	}
	return ;
}

void	change_color(int x, int y, int *color)
{
	int	red;
	int	green;
	int	blue;

	red = x;
	green = 0;
	blue = y;
	*color = (red << 16) + (green << 8) + blue;
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
	if (DEBUG)
		printf("memset succeeded \n");
}
