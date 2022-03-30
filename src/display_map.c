#include "fdf.h"

void	apply_matrix(t_fdf_cont *cont, t_angles *angles, t_point *p)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	(void) angles;
	(void) prev_x;
	(void) prev_y;
	(void) prev_z;
	// p->x -= (cont->map_w * cont->square_width) / 2;
	// p->y -= (cont->map_h * cont->square_width) / 2;
	p->x = p->x * cont->square_width;
	p->y = p->y * cont->square_width;
	p->z = p->z * cont->square_width * cont->z_divisor + 10;
	//rotate_x
	prev_y = p->y;
	prev_z = p->z;
	//added
	prev_x = p->x;
	p->y = angles->cos_x * prev_y - angles->sin_x * prev_z;
	p->z = angles->cos_x * prev_z + angles->sin_x * prev_y;
	//rotate_y
	prev_x = p->x;
	prev_z = p->z;
	p->x = angles->cos_y * prev_x + angles->sin_y * prev_z;
	p->z = angles->cos_y * prev_z - angles->sin_y * prev_x;
	//rotate_z
	prev_x = p->x;
	prev_y = p->y;
	p->x = angles->cos_z * prev_x - angles->sin_z * prev_y;
	p->y = angles->cos_z * prev_y + angles->sin_z * prev_x;
	if (cont->toggle_proj)
	{
		p->x /= p->z;
		p->y /= p->z;
	}


	p->x += (cont->win_w - cont->map_w) / 2 - cont->x_offset;
	p->y += (cont->win_h - cont->map_h) / 2 - cont->y_offset;
	p->x = round(p->x);
	p->y = round(p->y);
	p->z = round(p->z);
}

void	project_point(t_fdf_cont *cont, t_angles *angles, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p2.x = (cont->map[x + y * cont->map_w].x);
	p2.y = (cont->map[x + y * cont->map_w].y);
	p2.z = cont->map[x + y * cont->map_w].z;
	p2.color = cont->map[x + y * cont->map_w].color;
	apply_matrix(cont, angles, &p2);
	if (x)
	{
		p1.x = (cont->map[x - 1 + y * cont->map_w].x);
		p1.y = (cont->map[x - 1 + y * cont->map_w].y);
		p1.z = cont->map[x - 1 + y * cont->map_w].z;
		p1.color = cont->map[x - 1 + y * cont->map_w].color;
		apply_matrix(cont, angles, &p1);
		draw_line(cont, p1, p2);
	}
	if (y)
	{
		p1.x = (cont->map[x + (y - 1) * cont->map_w].x);
		p1.y = (cont->map[x + (y - 1) * cont->map_w].y);
		p1.z = cont->map[x + (y - 1) * cont->map_w].z;
		p1.color = cont->map[x + (y - 1) * cont->map_w].color;
		apply_matrix(cont, angles, &p1);
		draw_line(cont, p1, p2);
	}
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

t_angles calculate_angles(t_fdf_cont *cont)
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
	draw_background(cont->img, FDF_GREY);
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
	// print_map_info(cont, 0);
	return ;
}
