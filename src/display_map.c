#include "fdf.h"

bool	both_points_are_within_bounds(t_fdf_cont *cont, t_point p1, t_point p2)
{
	if (p1.x < 0 || p2.x < 0 || p1.y < 0 || p2.y < 0 || p1.x > cont->win_width \
		|| p2.x > cont->win_width || p1.y > cont->win_height || p2.y > cont->win_height)
		return (false);
	return (true);
}

void	project_point(t_fdf_cont *cont, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p2.x = (int)(cont->map[x + y * cont->map_width].x * cont->square_width) + cont->win_width / 2;
	p2.y = (int)(cont->map[x + y * cont->map_width].y * cont->square_width) + cont->win_height / 2;
	p2.z = cont->map[x + y * cont->map_width].z;
	p2.color = cont->map[x + y * cont->map_width].color;
	if (x > 0)
	{
		p1.x = (int)(cont->map[x - 1 + y * cont->map_width].x * cont->square_width) + cont->win_width / 2;
		p1.y = (int)(cont->map[x - 1 + y * cont->map_width].y * cont->square_width) + cont->win_height / 2;
		p1.z = cont->map[x - 1 + y * cont->map_width].z;
		if (both_points_are_within_bounds(cont, p1, p2))
			draw_line(cont->curr_img, p1, p2);
	}
	if (y > 0)
	{
		p1.x = (int)(cont->map[x + (y - 1) * cont->map_width].x * cont->square_width) + cont->win_width / 2;
		p1.y = (int)(cont->map[x + (y - 1) * cont->map_width].y * cont->square_width) + cont->win_height / 2;
		p1.z = cont->map[x + (y - 1) * cont->map_width].z;
		if (both_points_are_within_bounds(cont, p1, p2))
			draw_line(cont->curr_img, p1, p2);
	}
	return ;
}

void	scale_map(t_fdf_cont *cont)
{
	int	x;
	int	y;
	int	zoom;

	y = 0;
	if (cont->map_width)
		zoom = cont->win_width / cont->map_width / 2;
	if (cont->map_height && cont->win_height / cont->map_height - 1 < zoom)
		zoom = cont->win_height / cont->map_height / 2;
	while (y < cont->map_height)
	{
		x = 0;
		while (x < cont->map_width)
		{
			cont->map[x + y * cont->map_width].x *= 10;
			cont->map[x + y * cont->map_width].y *= 10;
			cont->map[x + y * cont->map_width].z *= 10;
			x++;
		}
		y++;
	}
	return ;
}

void	center_map(t_fdf_cont *cont)
{
	double	x_offset;
	double	y_offset;
	int		x;
	int		y;

	x_offset = -cont->map_width / 2;
	y_offset = -cont->map_height / 2;
	y = 0;
	while (y < cont->map_height)
	{
		x = 0;
		while (x < cont->map_width)
		{
			cont->map[x + y * cont->map_width].x += x_offset;
			cont->map[x + y * cont->map_width].y += y_offset;
			x++;
		}
		y++;
	}
	return ;
}

void	display_map(t_fdf_cont *cont)
{
	int	x;
	int	y;

	// rotate_map(cont);
	// scale_map(cont);
	// center_map(cont);
	draw_background(cont->curr_img, FDF_BLACK);
	if (DEBUG)
		print_map_info(cont, 0);
	y = 0;
	while (y < cont->map_height)
	{
		x = 0;
		while (x < cont->map_width)
		{
			project_point(cont, x, y);
			x++;
		}
		y++;
	}
	display_default(cont);
	return ;
}
