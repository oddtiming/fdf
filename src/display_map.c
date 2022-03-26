#include "fdf.h"

void	project_point(t_fdf_cont *cont, int x, int y)
{
	t_2d_point	p1;
	t_2d_point	p2;

	if (DEBUG)
		printf("x = %d\ny = %d\n", x, y);
	p2.x = (int)(cont->map[x + y * cont->map_width].x * 5) + WIN_W / 2 - (cont->map_width / 2) * 5;
	p2.y = (int)(cont->map[x + y * cont->map_width].y * 5) + WIN_H / 2 - (cont->map_height / 2) * 5;

	if (x > 0)
	{
		p1.x = (int)(cont->map[x - 1 + y * cont->map_width].x * 5) + WIN_W / 2 - (cont->map_width / 2) * 5;
		p1.y = (int)(cont->map[x - 1 + y * cont->map_width].y * 5) + WIN_H / 2 - (cont->map_height / 2) * 5;
		draw_line(cont->curr_img, p1, p2);
	}
	if (y > 0)
	{
		p1.x = (int)(cont->map[x + (y - 1) * cont->map_width].x * 5) + WIN_W / 2 - (cont->map_width / 2) * 5;
		p1.y = (int)(cont->map[x + (y - 1) * cont->map_width].y * 5) + WIN_H / 2 - (cont->map_height / 2) * 5;
		draw_line(cont->curr_img, p1, p2);
	}
	fill_pixel(cont->curr_img, p2.x, p2.y, 0xFF0000);
	return ;
}

void	scale_map(t_fdf_cont *cont)
{
	int	x;
	int	y;
	int	zoom;

	y = 0;
	if (cont->map_width)
		zoom = WIN_W / cont->map_width / 2;
	if (cont->map_height && WIN_H / cont->map_height - 1 < zoom)
		zoom = WIN_H / cont->map_height / 2;
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
	int	x;
	int	y;
	int	x_offset;
	int	y_offset;

	x_offset = WIN_W / 2 - cont->map_width / 2;
	y_offset = WIN_H / 2 - cont->map_height / 2;
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
