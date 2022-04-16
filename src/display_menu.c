/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:07:32 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/16 16:08:00 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	display_menu_translations(t_fdf_cont *cont)
{
	char	*x_offset;
	char	*y_offset;
	char	*z_offset;

	x_offset = ft_itoa(cont->x_offset);
	y_offset = ft_itoa(cont->y_offset);
	z_offset = ft_itoa(cont->z_offset);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 450, WHITE, "x trans:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 95, 450, WHITE, x_offset);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 150, 450, WHITE, "px");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 470, WHITE, "y trans:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 95, 470, WHITE, y_offset);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 150, 470, WHITE, "px");
	free(x_offset);
	free(y_offset);
	if (cont->toggle_proj)
	{
		free(z_offset);
		return ;
	}
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 490, WHITE, "z trans:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 95, 490, WHITE, z_offset);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 150, 490, WHITE, "px");
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
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 350, WHITE, "ZOOM:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 350, WHITE, zoom);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 120, 350, WHITE, "x");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 380, WHITE, "x rot:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 380, WHITE, theta_x);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 120, 380, WHITE, "deg");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 400, WHITE, "y rot:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 400, WHITE, theta_y);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 120, 400, WHITE, "deg");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 420, WHITE, "z rot:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 420, WHITE, theta_z);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 120, 420, WHITE, "deg");
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
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 250, WHITE, "WIN_W:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 250, WHITE, win_w);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 135, 250, WHITE, "px");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 270, WHITE, "WIN_H:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 270, WHITE, win_h);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 135, 270, WHITE, "px");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 300, WHITE, "MAP_W:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 300, WHITE, map_w);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 320, WHITE, "MAP_H:");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 320, WHITE, map_h);
	free(win_w);
	free(win_h);
	free(map_w);
	free(map_h);
}

static void	display_menu_background(t_fdf_cont *cont, int width, int height)
{
	int	x;
	int	y;

	y = height - 1;
	y = 0;
	while (y < cont->win_h)
	{
		x = 0;
		while (y >= height - 1 && x < width)
		{
			fill_pixel(cont->img, x, y, BLACK);
			x++;
		}
		while (x < width + 7)
		{
			fill_pixel(cont->img, x, y, GREY);
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

	img_ptr = NULL;
	height = 0;
	width = 0;
	img_ptr = mlx_xpm_file_to_image(
			cont->mlx_ptr, "./imgs/banner.xpm", &width, &height);
	display_menu_background(cont, width, height);
	display_img(cont, img_ptr);
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 15, 160, WHITE, "proj:");
	if (!cont->toggle_proj)
		mlx_string_put(cont->mlx_ptr, cont->win_ptr, 80, 160, RED, "PERSP");
	else
		mlx_string_put(cont->mlx_ptr, cont->win_ptr, 80, 160, YELLOW, "ORTHO");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 25, 190, WHITE, "Alt legend");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 50, 220, CYAN, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 70, 220, BLUE, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 90, 220, YELLOW, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 110, 220, RED, ">>");
	mlx_string_put(cont->mlx_ptr, cont->win_ptr, 130, 220, PINK, ">>");
	display_menu_dimensions(cont);
	display_menu_angles(cont);
	display_menu_translations(cont);
}
