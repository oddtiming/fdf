#include "fdf.h"
#include "fdf_hooks.h"

void	set_hooks(t_fdf_cont *cont)
{
	mlx_do_key_autorepeaton(cont->mlx_ptr);
	mlx_expose_hook(cont->win_ptr, handle_expose_hook, cont);
	mlx_key_hook(cont->win_ptr, handle_key_release_hook, cont);
	mlx_mouse_hook(cont->win_ptr, handle_mouse_hook, cont);
	mlx_loop_hook(cont->mlx_ptr, default_hook, cont);
	mlx_hook(cont->win_ptr, DESTROY_NOTIFY, 0, fdf_clean_exit, cont);
	mlx_hook(cont->win_ptr, 2, 1L<<0, handle_key_press_hook, cont);
	mlx_hook(cont->win_ptr, 6, 1L<<3, handle_mouse_motion, cont);
	return ;
}

int	default_hook(t_fdf_cont *cont)
{
	if (cont->toggle_menu)
		return (0);
	if (cont->toggle_rot_x == true)
		cont->theta_x += 0.0145;
	if (cont->toggle_rot_y == true)
		cont->theta_y += 0.0145;
	if (cont->toggle_rot_z == true)
		cont->theta_z += 0.0145;
	display_map(cont);
	return (0);
}

int	handle_expose_hook(t_fdf_cont *cont)
{
	t_fdf_cont	*mlx;

	mlx = (t_fdf_cont *)cont;
	return (0);
}

int	handle_key_release_hook(int keysym, t_fdf_cont *cont)
{
	if (keysym == KEY_ESC)
		fdf_clean_exit(cont);
	if (keysym == KEY_F1)
	{ 
		cont->toggle_menu = !cont->toggle_menu;
		display_menu(cont);
		return (0);
	}
	if (cont->toggle_menu)
		return (1);
	else if (keysym == KEY_C)
		cont->map_is_colored = !cont->map_is_colored;
	else if (keysym == KEY_P)
		cont->toggle_proj = !cont->toggle_proj;
	else if (keysym == KEY_R)
	{
		cont->toggle_rot_x = !cont->toggle_rot_x;
		cont->toggle_rot_y = !cont->toggle_rot_y;
		cont->toggle_rot_z = !cont->toggle_rot_z;
	}
	else if (keysym == NUMPAD9)
		cont->toggle_rot_z = !cont->toggle_rot_z;
	else if (keysym == NUMPAD6)
		cont->toggle_rot_y = !cont->toggle_rot_y;
	else if (keysym == NUMPAD3)
		cont->toggle_rot_x = !cont->toggle_rot_x;
	else if (keysym == NUMPAD0 || keysym == KEY_0)
		reset_proportions(cont);
	return (0);
}

int	handle_key_press_hook(int keysym, t_fdf_cont *cont)
{
	if (cont->toggle_menu)
		return (1);
	if (keysym == 69 || keysym == 24) //'+'
		if (cont->square_width < 150)
			cont->square_width += 1;
	if (keysym == 78 || keysym == 27) //'-'
		if (cont->square_width > 2)
			cont->square_width -= 1;
	if (keysym == 89) //NUMPAD7
		cont->theta_z -= 0.1;
	if (keysym == 91) //NUMPAD8
		cont->theta_z += 0.1;
	if (keysym == 86) //NUMPAD4
		cont->theta_y -= 0.1;
	if (keysym == 87) //NUMPAD5
		cont->theta_y += 0.1;
	if (keysym == 83) //NUMPAD1
		cont->theta_x -= 0.1;
	if (keysym == 84) //NUMPAD2
		cont->theta_x += 0.1;
	if (keysym == 13) //KEY_W
		if (cont->z_offset > -1000)
			cont->z_offset -= 8;
	if (keysym == 1) //KEY_S
		if (cont->z_offset < 2000)
			cont->z_offset += 8;
	if (keysym == 12) //KEY_Q
		if (cont->z_divisor > -5)
			cont->z_divisor -= 0.12;
	if (keysym == 14) //KEY_E
		if (cont->z_divisor < 5)
			cont->z_divisor += 0.12;
	if (keysym == 123 || keysym == 0) //KEY_LEFT || KEY_A
		if (cont->x_offset < cont->win_w * 0.1F * cont->square_width)
			cont->x_offset += 10;
	if (keysym == 124 || keysym == 2) //KEY_RIGHT || KEY_D
		if (cont->x_offset > cont->win_w * -0.1F * cont->square_width)
			cont->x_offset -= 10;
	if (keysym == 126 || keysym == 6) //KEY_UP || KEY_Z
		if (cont->y_offset < cont->win_h * 0.1F * cont->square_width)
			cont->y_offset += 10;
	if (keysym == 125 || keysym == 7) //KEY_DOWN || KEY_X
		if (cont->y_offset > cont->win_h * -0.1F * cont->square_width)
			cont->y_offset -= 10;
	return (0);
}

int	handle_mouse_hook(int button, int x, int y, t_fdf_cont *cont)
{
	if (button == 1 && !cont->toggle_menu)
	{
		cont->toggle_mouse_rot = !cont->toggle_mouse_rot;
		if (cont->toggle_mouse_rot)
		{
			cont->toggle_rot_x = false;
			cont->toggle_rot_y = false;
			cont->toggle_rot_z = false;
			cont->mouse_initial_xy = (x << 16) | y;
		}
	}
	return (0);
}

int	handle_mouse_motion(int x, int y, t_fdf_cont *cont)
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
