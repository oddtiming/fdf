#include "fdf.h"

void	project_perspective(t_fdf_cont *cont, t_point *p)
{

	p->x -= (cont->win_w - cont->map_w) / 2 - cont->x_offset;
	p->y -= (cont->win_h - cont->map_h) / 2 - cont->y_offset;
	p->x += cont->x_offset;
	p->y += cont->y_offset;
	p->z += cont->z_offset;
	p->x = (p->x * 100 * cont->square_width / p->z);
	p->y = (p->y * 100 * cont->square_width / p->z);
	p->x += (cont->win_w - cont->map_w) / 2;
	p->y += (cont->win_h - cont->map_h) / 2;
}

void	apply_matrix(t_fdf_cont *cont, t_angles *angles, t_point *p)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	p->x = p->x * cont->square_width;
	p->y = p->y * cont->square_width;
	// if (!cont->toggle_proj)
	// 	p->z = p->z * cont->square_width * cont->z_divisor + cont->z_offset;
	// else
	p->z = p->z * cont->square_width * cont->z_divisor;
	//rotate_x
	prev_y = p->y;
	prev_z = p->z;
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

	// if (!cont->toggle_proj)
	// {
	// 	p->z += cont->z_offset;
	// 	p->x = (p->x / p->z * 2 * cont->z_offset);
	// 	p->y = (p->y / p->z * 2 * cont->z_offset);
	// // }
	p->x += (cont->win_w - cont->map_w) / 2 - cont->x_offset;
	p->y += (cont->win_h - cont->map_h) / 2 - cont->y_offset;
	if (!cont->toggle_proj)
		project_perspective(cont, p);
	// else
	// {
	// }


	p->x = round(p->x);
	p->y = round(p->y);
	p->z = round(p->z);
}

void	project_point(t_fdf_cont *cont, t_angles *angles, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p2 = cont->map[x + y * cont->map_w];
	apply_matrix(cont, angles, &p2);
	if (x)
	{
		p1 = cont->map[x - 1 + y * cont->map_w];
		apply_matrix(cont, angles, &p1);
		draw_line(cont, p1, p2);
	}
	if (y)
	{
		p1 = cont->map[x + (y - 1) * cont->map_w];
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
