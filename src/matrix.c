#include "fdf.h"

void	center_map(t_fdf_cont *cont)
{
	double	x_center;
	double	y_center;
	int		x;
	int		y;

	x_center = cont->map_w / 2;
	y_center = cont->map_h / 2;
	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			cont->map[x + y * cont->map_w].x -= x_center;
			cont->map[x + y * cont->map_w].y -= y_center;
			x++;
		}
		y++;
	}
	return ;
}

void	apply_scale(t_fdf_cont *cont, t_point *p)
{
	p->x *= cont->square_width;
	p->y *= cont->square_width;
	p->z *= cont->square_width * cont->z_divisor;
}

void	apply_rotation(t_angles *angles, t_point *p)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	prev_y = p->y;
	prev_z = p->z;
	p->y = angles->cos_x * prev_y - angles->sin_x * prev_z;
	p->z = angles->cos_x * prev_z + angles->sin_x * prev_y;
	prev_x = p->x;
	prev_z = p->z;
	p->x = angles->cos_y * prev_x + angles->sin_y * prev_z;
	p->z = angles->cos_y * prev_z - angles->sin_y * prev_x;
	prev_x = p->x;
	prev_y = p->y;
	p->x = angles->cos_z * prev_x - angles->sin_z * prev_y;
	p->y = angles->cos_z * prev_y + angles->sin_z * prev_x;
}

void	apply_translation(t_fdf_cont *cont, t_point *p)
{
	p->x += cont->win_w / 2;
	p->y += cont->win_h / 2;
	p->x -= cont->x_offset;
	p->y -= cont->y_offset;
}

void	apply_matrix(t_fdf_cont *cont, t_angles *angles, t_point *p)
{
	apply_scale(cont, p);
	apply_rotation(angles, p);
	apply_translation(cont, p);
	if (!cont->toggle_proj)
		project_perspective(cont, p);
	p->x = round(p->x);
	p->y = round(p->y);
	p->z = round(p->z);
}
