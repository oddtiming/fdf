#include "fdf.h"

void	rotate_z(t_fdf_cont *cont, double theta)
{
	double	prev_x;
	double	prev_y;
	int		x;
	int		y;

	y = 0;
	while (y < cont->map_height)
	{
		x = 0;
		while (x < cont->map_width)
		{
			prev_x = cont->map[x + y * cont->map_width].x;
			prev_y = cont->map[x + y * cont->map_width].y;
			cont->map[x + y * cont->map_width].x = cos(theta) * prev_x - sin(theta) * prev_y;
			cont->map[x + y * cont->map_width].y = sin(theta) * prev_x + cos(theta) * prev_y;
			x++;
		}
		y++;
	}
}

void	rotate_matrix(t_fdf_cont *cont, int x, int y)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	(void)prev_x;
	(void)prev_y;
	(void)prev_z;
	prev_y = cont->map[x + y * cont->map_width].y;
	prev_z = cont->map[x + y * cont->map_width].z;
	cont->map[x + y * cont->map_width].y = cos(-0.7854) * prev_y - sin(-0.7854) * prev_z;
	cont->map[x + y * cont->map_width].z = sin(-0.7854) * prev_y + cos(-0.7854) * prev_z;
	prev_x = cont->map[x + y * cont->map_width].x;
	prev_z = cont->map[x + y * cont->map_width].z;
	cont->map[x + y * cont->map_width].x = cos(-0.7854) * prev_x + sin(-0.7854) * prev_z;
	cont->map[x + y * cont->map_width].z = -sin(-0.7854) * prev_x + cos(-0.7854) * prev_z;
	prev_x = cont->map[x + y * cont->map_width].x;
	prev_y = cont->map[x + y * cont->map_width].y;
	cont->map[x + y * cont->map_width].x = cos(-0.7854) * prev_x - sin(-0.7854) * prev_y;
	cont->map[x + y * cont->map_width].y = sin(-0.7854) * prev_x + cos(-0.7854) * prev_y;
}

void	rotate_map(t_fdf_cont *cont)
{
	int	x;
	int	y;

	y = 0;
	while (y < cont->map_height)
	{
		x = 0;
		while (x < cont->map_width)
		{
			rotate_matrix(cont, x, y);
			x++;
		}
		y++;
	}
}