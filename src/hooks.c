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
	if (cont->toggle_rot_x == true)
		rotate_x(cont, +0.0145);
	if (cont->toggle_rot_y == true)
		rotate_y(cont, +0.0145);
	if (cont->toggle_rot_z == true)
		rotate_z(cont, +0.0145);
	if (cont->toggle_rot_x || cont->toggle_rot_y || cont->toggle_rot_z)
		display_map(cont);
	(void) cont;
	return (0);
}


int	handle_expose_hook(t_fdf_cont *cont)
{
	t_fdf_cont	*mlx;

	mlx = (t_fdf_cont *)cont;
	if (DEBUG)
	{
		printf("Expose_hook has been called! \n");
		printf("data_arrd = %p \n", cont->img->data_addr);
		printf("img_ptr = %p \n", cont->img->img_ptr);
		printf("bpp = %d \n", cont->img->bpp);
		printf("line_len = %d \n", cont->img->line_len);
		printf("endian = %d \n", cont->img->endian);
	}
	return (0);
}

int	handle_key_hook(int keysym, t_fdf_cont *cont)
{
	if (DEBUG)
	{
		printf("Keysim = %d\n", keysym);
		printf("cont->img->data_addr %p\n", cont->img->data_addr);
		printf("cont->img->bpp %d\n", cont->img->bpp);
		printf("cont->img->line_len %d\n", cont->img->line_len);
		printf("cont->img->width %d\n", cont->img->width);
		printf("cont->img->height %d\n", cont->img->height);
		printf("cont->height %d\n", cont->map_height);
		printf("cont->width %d\n", cont->map_width);
		printf("Keysim = %d\n", keysym);
	}
	if (keysym == 53) //KEY_ESC
	{
		fdf_cleanup(cont);
		exit(0);
	}
	if (keysym == 2) //KEY_D
	{
		display_default(cont);
	}
	if (keysym == 37) //KEY_L
	{
		test_display_lines(cont);
	}
	if (keysym == 15) //KEY_R
	{
		display_square_rainbow(cont);
	}
	if (keysym == 18) //KEY_1
	{
		test_display_lines_multicolor(cont);
	}
	if (keysym == 76) //NUMPAD_ENTER
	{
		print_map_info(cont, 0);
	}
	if (keysym == 92) //NUMPAD9
	{
		cont->toggle_rot_z = !cont->toggle_rot_z;
	}
	if (keysym == 88) //NUMPAD6
	{
		cont->toggle_rot_y = !cont->toggle_rot_y;
	}
	if (keysym == 85) //NUMPAD3
	{
		cont->toggle_rot_x = !cont->toggle_rot_x;
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
	t_fdf_cont	*mlx;

	mlx = (t_fdf_cont *)cont;
	if (DEBUG)
	{
		printf("Keysim = %d\n", keysym);
		printf("cont->img->data_addr %p\n", cont->img->data_addr);
		printf("cont->img->bpp %d\n", cont->img->bpp);
		printf("cont->img->line_len %d\n", cont->img->line_len);
		printf("cont->img->width %d\n", cont->img->width);
		printf("cont->img->height %d\n", cont->img->height);
		printf("cont->height %d\n", cont->map_height);
		printf("cont->width %d\n", cont->map_width);
		printf("Keysim = %d\n", keysym);
	}
	if (keysym == 18) //KEY_1
	{
		test_display_lines_multicolor(mlx);
	}
	if (keysym == 89) //NUMPAD7
	{
		rotate_z(mlx, -0.1);
		display_map(cont);
	}
	if (keysym == 91) //NUMPAD8
	{
		rotate_z(mlx, +0.1);
		display_map(cont);
	}
	if (keysym == 86) //NUMPAD4
	{
		rotate_y(mlx, -0.1);
		display_map(cont);
	}
	if (keysym == 87) //NUMPAD5
	{
		rotate_y(mlx, +0.1);
		display_map(cont);
	}
	if (keysym == 83) //NUMPAD1
	{
		rotate_x(mlx, -0.1);
		display_map(cont);
	}
	if (keysym == 84) //NUMPAD2
	{
		rotate_x(mlx, +0.1);
		display_map(cont);
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
