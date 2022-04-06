#include "fdf.h"

void	set_hooks(t_fdf_cont *cont)
{
	mlx_do_key_autorepeaton(cont->mlx_ptr);
	mlx_expose_hook(cont->win_ptr, handle_expose_hook, cont);
	mlx_key_hook(cont->win_ptr, handle_key_hook, cont);
	mlx_mouse_hook(cont->win_ptr, handle_mouse_hook, cont);
	mlx_loop_hook(cont->mlx_ptr, handle_default_hook, cont);
	mlx_hook(cont->win_ptr, DESTROY_NOTIFY, 0, fdf_clean_exit, cont);
	mlx_hook(cont->win_ptr, 2, 1L<<0, handle_keypress_hook, cont);
	return ;
}

int	handle_default_hook(t_fdf_cont *cont)
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
	(void) cont;
	return (0);
}


int	handle_expose_hook(t_fdf_cont *cont)
{
	t_fdf_cont	*mlx;

	mlx = (t_fdf_cont *)cont;
	return (0);
}

int	handle_key_hook(int keysym, t_fdf_cont *cont)
{
	if (DEBUG)
	{
		printf("keysym = %d \n", keysym);
	}
	if (keysym == 53) //KEY_ESC
	{
		fdf_cleanup(cont);
		exit(0);
	}
	if (keysym == 122) //KEY_F1
	{ 
		cont->toggle_menu = !cont->toggle_menu;
		display_menu(cont);
		return (0);
	}
	if (cont->toggle_menu)
		return (1);
	else if (keysym == 8) //KEY_C
		cont->map_is_colored = !cont->map_is_colored;
	else if (keysym == 35) //KEY_P
		cont->toggle_proj = !cont->toggle_proj;
	else if (keysym == 15) //KEY_R
	{
		cont->toggle_rot_x = !cont->toggle_rot_x;
		cont->toggle_rot_y = !cont->toggle_rot_y;
		cont->toggle_rot_z = !cont->toggle_rot_z;
	}
	else if (keysym == 18) //KEY_1
		test_display_lines_multicolor(cont);
	else if (keysym == 76) //NUMPAD_ENTER
		print_map_info(cont, 0);
	else if (keysym == 92) //NUMPAD9
		cont->toggle_rot_z = !cont->toggle_rot_z;
	else if (keysym == 88) //NUMPAD6
		cont->toggle_rot_y = !cont->toggle_rot_y;
	else if (keysym == 85) //NUMPAD3
		cont->toggle_rot_x = !cont->toggle_rot_x;
	else if (keysym == 82) //NUMPAD0
	{
		cont->toggle_rot_x = false;
		cont->toggle_rot_y = false;
		cont->toggle_rot_z = false;
		cont->x_offset = 0;
		cont->y_offset = 0;
		cont->z_offset = 15;
		cont->square_width = ft_min(20, ft_max(683 / cont->map_h, 853 / cont->map_w));
		cont->z_divisor = 1;
		cont->map_is_colored = true;
		cont->theta_x = 0.5236;
		cont->theta_y = 0.5236;
		cont->theta_z = 0.5236;
	}
	if (keysym == 40) //KEY_K
	{ 
		void	*img_ptr;
		int		height;
		int		width;

		img_ptr = NULL;
		height = 0;
		width = 0;
		img_ptr = mlx_xpm_file_to_image(cont->mlx_ptr, "./extra_stuff_not_important/sexy_kermit.xpm", &width, &height);
		mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img_ptr, 0, 0);
	}
	return (0);
}

int	handle_keypress_hook(int keysym, t_fdf_cont *cont)
{
	if (cont->toggle_menu)
		return (1);
	else if (keysym == 18) //KEY_1
	{
		test_display_lines_multicolor(cont);
	}
	if (keysym == 69 || keysym == 24) //'+'
	{
		if (cont->square_width < 150)
		{
			cont->square_width += 1;
		}
		// display_map(cont);
	}
	if (keysym == 78 || keysym == 27) //'-'
	{
		if (cont->square_width > 2)
		{
			cont->square_width -= 1;
		}
	}
	if (keysym == 89) //NUMPAD7
	{
		cont->theta_z -= 0.1;
	}
	if (keysym == 91) //NUMPAD8
	{
		cont->theta_z += 0.1;
	}
	if (keysym == 86) //NUMPAD4
	{
		cont->theta_y -= 0.1;
	}
	if (keysym == 87) //NUMPAD5
	{
		cont->theta_y += 0.1;
	}
	if (keysym == 83) //NUMPAD1
	{
		cont->theta_x -= 0.1;
	}
	if (keysym == 84) //NUMPAD2
	{
		cont->theta_x += 0.1;
	}
	if (keysym == 13) //KEY_W
	{
		if (cont->z_offset > -1000)
			cont->z_offset -= 8;
	}
	if (keysym == 1) //KEY_S
	{
		if (cont->z_offset < 1000)
			cont->z_offset += 8;
	}
	if (keysym == 12) //KEY_Q
	{
		if (cont->z_divisor > -5)
			cont->z_divisor -= 0.12;
	}
	if (keysym == 14) //KEY_E
	{
		if (cont->z_divisor < 5)
			cont->z_divisor += 0.12;
	}
	if (keysym == 123 || keysym == 0) //KEY_LEFT || KEY_A
	{
		if (cont->x_offset < cont->win_w * 0.1F * cont->square_width)
			cont->x_offset += 10;
	}
	if (keysym == 124 || keysym == 2) //KEY_RIGHT || KEY_D
	{
		if (cont->x_offset > cont->win_w * -0.1F * cont->square_width)
			cont->x_offset -= 10;
	}
	if (keysym == 126 || keysym == 6) //KEY_UP || KEY_Z
	{
		if (cont->y_offset < cont->win_h * 0.1F * cont->square_width)
			cont->y_offset += 10;
	}
	if (keysym == 125 || keysym == 7) //KEY_DOWN || KEY_X
	{
		if (cont->y_offset > cont->win_h * -0.1F * cont->square_width)
			cont->y_offset -= 10;
	}
	return (0);
}

int	handle_mouse_hook(int button, int x, int y, t_fdf_cont *cont)
{
	t_fdf_cont	*mlx;

	mlx = (t_fdf_cont *)cont;
	if (DEBUG)
	{
		printf("Mouse coordinates (X: %d, Y: %d)\n", x, y);
		printf("Button pressed: %d \n", button);
	}
	return (0);
}
