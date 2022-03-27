#include "fdf.h"

void	rotate_z(t_fdf_cont *cont, double theta)
{
	double	prev_x;
	double	prev_y;
	double	sin_theta;
	double	cos_theta;
	int		x;
	int		y;

	sin_theta = sin(theta);
	cos_theta = cos(theta);
	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			prev_x = cont->map[x + y * cont->map_w].x;
			prev_y = cont->map[x + y * cont->map_w].y;
			cont->map[x + y * cont->map_w].x = cos_theta * prev_x - sin_theta * prev_y;
			cont->map[x + y * cont->map_w].y = cos_theta * prev_y + sin_theta * prev_x;
			x++;
		}
		y++;
	}
}

void	rotate_y(t_fdf_cont *cont, double theta)
{
	double	prev_x;
	double	prev_z;
	double	sin_theta;
	double	cos_theta;
	int		x;
	int		y;

	sin_theta = sin(theta);
	cos_theta = cos(theta);
	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			prev_x = cont->map[x + y * cont->map_w].x;
			prev_z = cont->map[x + y * cont->map_w].z;
			cont->map[x + y * cont->map_w].x = cos_theta * prev_x + sin_theta * prev_z;
			cont->map[x + y * cont->map_w].z = cos_theta * prev_z - sin_theta * prev_x;
			x++;
		}
		y++;
	}
}

void	rotate_x(t_fdf_cont *cont, double theta)
{
	double	prev_y;
	double	prev_z;
	double	sin_theta;
	double	cos_theta;
	int		x;
	int		y;

	sin_theta = sin(theta);
	cos_theta = cos(theta);
	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			prev_y = cont->map[x + y * cont->map_w].y;
			prev_z = cont->map[x + y * cont->map_w].z;
			cont->map[x + y * cont->map_w].y = cos_theta * prev_y - sin_theta * prev_z;
			cont->map[x + y * cont->map_w].z = cos_theta * prev_z + sin_theta * prev_y;
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
	prev_y = cont->map[x + y * cont->map_w].y;
	prev_z = cont->map[x + y * cont->map_w].z;
	cont->map[x + y * cont->map_w].y = cos(-0.5236) * prev_y - sin(-0.5236) * prev_z;
	cont->map[x + y * cont->map_w].z = sin(-0.5236) * prev_y + cos(-0.5236) * prev_z;
	prev_x = cont->map[x + y * cont->map_w].x;
	prev_z = cont->map[x + y * cont->map_w].z;
	cont->map[x + y * cont->map_w].x = cos(-0.5236) * prev_x + sin(-0.5236) * prev_z;
	cont->map[x + y * cont->map_w].z = -sin(-0.5236) * prev_x + cos(-0.5236) * prev_z;
	prev_x = cont->map[x + y * cont->map_w].x;
	prev_y = cont->map[x + y * cont->map_w].y;
	cont->map[x + y * cont->map_w].x = cos(-0.5236) * prev_x - sin(-0.5236) * prev_y;
	cont->map[x + y * cont->map_w].y = sin(-0.5236) * prev_x + cos(-0.5236) * prev_y;
}

void	rotate_map(t_fdf_cont *cont)
{
	int	x;
	int	y;

	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			rotate_matrix(cont, x, y);
			x++;
		}
		y++;
	}
}
