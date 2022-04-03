#include "fdf.h"

void	display_menu_translations(t_fdf_cont *cont)
{
	char	*x_offset;
	char	*y_offset;
	char	*z_offset;

	x_offset = ft_itoa(cont->x_offset);
	y_offset = ft_itoa(cont->y_offset);
	z_offset = ft_itoa(cont->z_offset);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 450, FDF_WH, "x trans:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 95, 450, FDF_WH, x_offset);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 150, 450, FDF_WH, "px");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 470, FDF_WH, "y trans:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 95, 470, FDF_WH, y_offset);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 150, 470, FDF_WH, "px");
	if (!cont->toggle_proj)
	{
		mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 490, FDF_WH, "z trans:");
		mlx_string_put(cont->mlx_ptr, cont->win_ptr, 95, 490, FDF_WH, z_offset);
		mlx_string_put(cont->mlx_ptr, cont->win_ptr, 150, 490, FDF_WH, "px");
	}
	free(x_offset);
	free(y_offset);
	free(z_offset);
}

void	display_menu_angles(t_fdf_cont *cont)
{
	char	*zoom;
	char	*theta_x;
	char	*theta_y;
	char	*theta_z;

	zoom = ft_itoa(cont->square_width);
	theta_x = ft_itoa((int)(cont->theta_x * 57.2958) % 360);
	theta_y = ft_itoa((int)(cont->theta_y * 57.2958) % 360);
	theta_z = ft_itoa((int)(cont->theta_z * 57.2958) % 360);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 350, FDF_WH, "ZOOM:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 350, FDF_WH, zoom);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 120, 350, FDF_WH, "x");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 380, FDF_WH, "x rot:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 380, FDF_WH, theta_x);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 120, 380, FDF_WH, "deg");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 400, FDF_WH, "y rot:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 400, FDF_WH, theta_y);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 120, 400, FDF_WH, "deg");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 420, FDF_WH, "z rot:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 420, FDF_WH, theta_z);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 120, 420, FDF_WH, "deg");
	free(zoom);
	free(theta_x);
	free(theta_y);
	free(theta_z);
}

void	display_menu_dimensions(t_fdf_cont *cont)
{
	char	*win_w;
	char	*win_h;
	char	*map_w;
	char	*map_h;

	win_w = ft_itoa(cont->win_w);
	win_h = ft_itoa(cont->win_h);
	map_w = ft_itoa(cont->map_w);
	map_h = ft_itoa(cont->map_h);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 250, FDF_WH, "WIN_W:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 250, FDF_WH, win_w);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 135, 250, FDF_WH, "px");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 270, FDF_WH, "WIN_H:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 270, FDF_WH, win_h);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 135, 270, FDF_WH, "px");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 300, FDF_WH, "MAP_W:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 300, FDF_WH, map_w);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 320, FDF_WH, "MAP_H:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 320, FDF_WH, map_h);
	free(win_w);
	free(win_h);
	free(map_w);
	free(map_h);
}

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
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 160, FDF_WH, "proj:");
	if (!cont->toggle_proj)
		mlx_string_put(cont->mlx_ptr, cont->win_ptr, 80, 160, FDF_RED, "PERSP");
	else
		mlx_string_put(cont->mlx_ptr, cont->win_ptr, 80, 160, FDF_YELLOW, "ORTHO");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 25, 190, FDF_WH, "Altitude legend");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 50, 220, FDF_CYAN, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 70, 220, FDF_BLUE, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 220, FDF_YELLOW, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 110, 220, FDF_RED, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 130, 220, FDF_PINK, ">>");
	display_menu_dimensions(cont);
	display_menu_angles(cont);
	display_menu_translations(cont);

}
