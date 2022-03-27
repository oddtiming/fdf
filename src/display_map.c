#include "fdf.h"

bool	is_within_bounds(t_fdf_cont *cont, t_point const *const p)
{
	if (p->x < 0 || p->y < 0 || p->x > cont->win_w || p->y > cont->win_h)
		return (false);
	return (true);
}

void	project_point(t_fdf_cont *cont, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p2.x = (int)(cont->map[x + y * cont->map_w].x * cont->square_width) + cont->x_offset;
	p2.y = (int)(cont->map[x + y * cont->map_w].y * cont->square_width) + cont->y_offset;
	p2.z = cont->map[x + y * cont->map_w].z * cont->alt_offset * cont->z_divisor;
	p2.color = cont->map[x + y * cont->map_w].color;
	if (x)
	{
		p1.x = (int)(cont->map[x - 1 + y * cont->map_w].x * cont->square_width) + cont->x_offset;
		p1.y = (int)(cont->map[x - 1 + y * cont->map_w].y * cont->square_width) + cont->y_offset;
		p1.z = cont->map[x - 1 + y * cont->map_w].z * cont->alt_offset * cont->z_divisor;
		p1.color = cont->map[x - 1 + y * cont->map_w].color;
		if (is_within_bounds(cont, &p2) || is_within_bounds(cont, &p1))
			draw_line(cont, p1, p2);
	}
	if (y)
	{
		p1.x = (int)(cont->map[x + (y - 1) * cont->map_w].x * cont->square_width) + cont->x_offset;
		p1.y = (int)(cont->map[x + (y - 1) * cont->map_w].y * cont->square_width) + cont->y_offset;
		p1.z = cont->map[x + (y - 1) * cont->map_w].z * cont->alt_offset * cont->z_divisor;
		p1.color = cont->map[x + (y - 1) * cont->map_w].color;
		if (is_within_bounds(cont, &p2) || is_within_bounds(cont, &p1))
			draw_line(cont, p1, p2);
	}
	// p1.x = (int)(cont->map[x + (y - 2) * cont->map_w].x * cont->square_width) + cont->x_offset;
	// p1.y = (int)(cont->map[x + (y - 2) * cont->map_w].y * cont->square_width) + cont->y_offset;
	// p1.z = 1000;
	// p1.color = cont->map[x + (y - 2) * cont->map_w].color;
	// if (is_within_bounds(cont, &p2) || is_within_bounds(cont, &p1))
	// 	draw_line(cont, p1, p2);
	// p1.x = (int)(cont->map[x + (y - 3) * cont->map_w].x * cont->square_width) + cont->x_offset;
	// p1.y = (int)(cont->map[x + (y - 3) * cont->map_w].y * cont->square_width) + cont->y_offset;
	// p1.z = 1000;
	// p1.color = cont->map[x + (y - 3) * cont->map_w].color;
	// if (is_within_bounds(cont, &p2) || is_within_bounds(cont, &p1))
	// 	draw_line(cont, p1, p2);
	// p1.x = (int)(cont->map[x + (y - 4) * cont->map_w].x * cont->square_width) + cont->x_offset;
	// p1.y = (int)(cont->map[x + (y - 4) * cont->map_w].y * cont->square_width) + cont->y_offset;
	// p1.z = 1000;
	// p1.color = cont->map[x + (y - 4) * cont->map_w].color;
	// if (is_within_bounds(cont, &p2) || is_within_bounds(cont, &p1))
	// 	draw_line(cont, p1, p2);
	// p1.x = (int)(cont->map[x + 1 + y * cont->map_w].x * cont->square_width) + cont->x_offset;
	// p1.y = (int)(cont->map[x + 1 + y * cont->map_w].y * cont->square_width) + cont->y_offset;
	// p1.z = cont->map[x + 1 + y * cont->map_w].z * cont->alt_offset * cont->z_divisor;
	// p1.color = cont->map[x + 1 + y * cont->map_w].color;
	// if (is_within_bounds(cont, &p2) || is_within_bounds(cont, &p1))
	// 	draw_line(cont, p1, p2);
	// p1.x = (int)(cont->map[x + (y + 1) * cont->map_w].x * cont->square_width) + cont->x_offset;
	// p1.y = (int)(cont->map[x + (y + 0) * cont->map_w].y * cont->square_width) + cont->y_offset;
	// p1.z = 1000;
	// p1.color = cont->map[x + (y) * cont->map_w].color;
	// if (is_within_bounds(cont, &p2) || is_within_bounds(cont, &p1))
	// 	draw_line(cont, p1, p2);
	// p1.x = (int)(cont->map[x + (y + 2) * cont->map_w].x * cont->square_width) + cont->x_offset;
	// p1.y = (int)(cont->map[x + (y + 0) * cont->map_w].y * cont->square_width) + cont->y_offset;
	// p1.z = 1000;
	// p1.color = cont->map[x + (y) * cont->map_w].color;
	// if (is_within_bounds(cont, &p2) || is_within_bounds(cont, &p1))
	// 	draw_line(cont, p1, p2);
	// p1.x = (int)(cont->map[x + (y + 3) * cont->map_w].x * cont->square_width) + cont->x_offset;
	// p1.y = (int)(cont->map[x + (y + 0) * cont->map_w].y * cont->square_width) + cont->y_offset;
	// p1.z = 1000;
	// p1.color = cont->map[x + (y) * cont->map_w].color;
	// if (is_within_bounds(cont, &p2) || is_within_bounds(cont, &p1))
	// 	draw_line(cont, p1, p2);
	// p1.x = (int)(cont->map[x + (y + 4) * cont->map_w].x * cont->square_width) + cont->x_offset;
	// p1.y = (int)(cont->map[x + (y + 0) * cont->map_w].y * cont->square_width) + cont->y_offset;
	// p1.z = 1000;
	// p1.color = cont->map[x + (y) * cont->map_w].color;
	// if (is_within_bounds(cont, &p2) || is_within_bounds(cont, &p1))
	// 	draw_line(cont, p1, p2);
}

void	scale_map(t_fdf_cont *cont)
{
	int	x;
	int	y;
	int	zoom;

	y = 0;
	if (cont->map_w)
		zoom = cont->win_w / cont->map_w / 2;
	if (cont->map_h && cont->win_h / cont->map_h - 1 < zoom)
		zoom = cont->win_h / cont->map_h / 2;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			cont->map[x + y * cont->map_w].x *= 10;
			cont->map[x + y * cont->map_w].y *= 10;
			cont->map[x + y * cont->map_w].z *= 10;
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

	x_offset = -cont->map_w / 2;
	y_offset = -cont->map_h / 2;
	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			cont->map[x + y * cont->map_w].x += x_offset;
			cont->map[x + y * cont->map_w].y += y_offset;
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

	rotate_map(cont);
	// scale_map(cont);
	// center_map(cont);
	draw_background(cont->img, FDF_BLACK);
	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			project_point(cont, x, y);
			x++;
		}
		y++;
	}
	display_default(cont);
	return ;
}
