#include "fdf.h"
#include "fdf_hooks.h"

int	handle_mouse_hook(int button, int x, int y, t_fdf *cont)
{
	if (button == 1 && !cont->toggle_menu)
	{
		cont->toggle_mouse_rot = !cont->toggle_mouse_rot;
		if (cont->toggle_mouse_rot)
		{
			cont->toggle_rot_x = false;
			cont->toggle_rot_y = false;
			cont->toggle_rot_z = false;
		}
	}
	(void)x;
	(void)y;
	return (0);
}

int	handle_mouse_motion(int x, int y, t_fdf *cont)
{
	double	x_percent;
	double	y_percent;

	if (!cont->toggle_mouse_rot || cont->toggle_menu)
		return (0);
	x_percent = (double)x / (double)cont->win_w;
	y_percent = (double)y / (double)cont->win_h;
	cont->theta_y = x_percent * TWO_PI * (-1);
	cont->theta_x = y_percent * TWO_PI * (-1);
	return (0);
}
