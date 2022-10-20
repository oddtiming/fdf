#include "fdf.h"

void	project_perspective(t_fdf *cont, t_point *p)
{
	p->x -= cont->win_w / 2 - cont->x_offset;
	p->y -= cont->win_h / 2 - cont->y_offset;
	p->x += cont->x_offset;
	p->y += cont->y_offset;
	p->z += cont->z_offset;
	p->x = (p->x * 80 * cont->square_width / p->z);
	p->y = (p->y * 80 * cont->square_width / p->z);
	p->x += cont->win_w / 2;
	p->y += cont->win_h / 2;
}

void	cycle_orthographic_perspectives(t_fdf *cont)
{
	static int	switch_counter;

	cont->toggle_rot_x = false;
	cont->toggle_rot_y = false;
	cont->toggle_rot_z = false;
	if (switch_counter == 0)
	{
		cont->theta_x = 0;
		cont->theta_y = 0;
		cont->theta_z = 0;
	}
	else if (switch_counter == 1)
	{
		cont->theta_x = 0;
		cont->theta_y = 1.5708;
		cont->theta_z = 0;
	}
	else if (switch_counter == 2)
	{
		cont->theta_x = 1.5708;
		cont->theta_y = 0;
		cont->theta_z = 0;
	}
	switch_counter = (switch_counter + 1) % 3;
}
