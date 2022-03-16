#include "fdf.h"

int	handle_default_hook(t_fdf_cont *cont)
{
	display_square(cont);
	return (0);
}


int	handle_expose_hook(t_fdf_cont *cont)
{
	t_fdf_cont	*mlx;
	char	*data_addr;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	mlx = (t_fdf_cont *)cont;
	img_ptr = NULL;
	bits_per_pixel = 0;
	size_line = 0;
	endian = 0;
	data_addr = NULL;
	if (DEBUG)
	{
		printf("Expose_hook has been called! \n");
		printf("data_arrd = %p \n", data_addr);
		printf("img_ptr = %p \n", img_ptr);
		printf("bits_per_pixel = %d \n", bits_per_pixel);
		printf("size_line = %d \n", size_line);
		printf("endian = %d \n", endian);
	}
	return (0);
}

int	handle_key_hook(int keysym, t_fdf_cont *cont)
{
	t_fdf_cont	*mlx;

	mlx = (t_fdf_cont *)cont;
	if (DEBUG)
	{
		printf("Keysim = %d\n", keysym);
	}
	if (keysym == 53)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(1);
	}
	if (keysym == 1)
	{
		display_square(mlx);
	}
	if (keysym == 40)
	{
		void	*img_ptr;
		int		height;
		int		width;

		img_ptr = NULL;
		height = 0;
		width = 0;
		img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./extra_stuff_not_important/sexy_kermit.xpm", &width, &height);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img_ptr, 0, 0);
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
