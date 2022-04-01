#include "fdf.h"

void	display_menu_background(t_fdf_cont *cont, int menu_width, int menu_height)
{
	int	x;
	int	y;

	y = menu_height - 1;
	y = 0;
	while (y < cont->win_h)
	{
		x = 0;
		while (y >= menu_height - 1 && x < menu_width)
		{
			fill_pixel(cont->img, x, y, FDF_BLACK);
			x++;
		}
		while (x < menu_width + 7)
		{
			fill_pixel(cont->img, x, y, FDF_GREY);
			x++;
		}
		y++;
	}
	display_default(cont);
}

void	display_menu(t_fdf_cont *cont)
{
	void	*img_ptr;
	int		height;
	int		width;

	if (!cont->toggle_menu)
		return ;
	img_ptr = NULL;
	height = 0;
	width = 0;
	img_ptr = mlx_xpm_file_to_image(cont->mlx_ptr, "./extra_stuff_not_important/banner.xpm", &width, &height);
	display_menu_background(cont, width, height);
	mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img_ptr, 0, 0);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 25, 160, FDF_CYAN, "hey there");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 25, 190, FDF_WHITE, "Altitude legend");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 50, 220, FDF_CYAN, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 70, 220, FDF_BLUE, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 220, FDF_YELLOW, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 110, 220, FDF_RED, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 130, 220, FDF_PINK, ">>");
}
