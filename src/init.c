/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:17:30 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/15 23:04:45 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_proportions(t_fdf_cont *cont)
{
	cont->toggle_rot_x = false;
	cont->toggle_rot_y = false;
	cont->toggle_rot_z = false;
	cont->map_is_colored = true;
	cont->toggle_mouse_rot = false;
	cont->square_width = ft_min(20,
			ft_max(683 / cont->map_h, 853 / cont->map_w));
	cont->x_offset = 0;
	cont->y_offset = 0;
	cont->z_offset = 1000;
	cont->theta_x = 0.5236;
	cont->theta_y = 0.5236;
	cont->theta_z = 0.5236;
	cont->z_divisor = 1.0F;
}

void	fdf_init(t_fdf_cont *cont, char *filepath)
{
	t_img	*img;

	cont->mlx_ptr = mlx_init();
	if (!cont->mlx_ptr)
		exit_on_err("mlx: mlx_init() error \n");
	cont->win_name = ft_get_last_token(filepath, '/');
	cont->win_ptr = mlx_new_window(
			cont->mlx_ptr, cont->win_w, cont->win_h, cont->win_name);
	if (!cont->win_ptr)
		exit_on_err("mlx: mlx_new_window() error \n");
	cont->img = malloc(sizeof(t_img));
	if (!cont->img)
		exit_on_err("fdf_init: malloc error \n");
	img = cont->img;
	img->width = cont->win_w;
	img->height = cont->win_h;
	img->img_ptr = mlx_new_image(cont->mlx_ptr, img->width, img->height);
	img->data_addr = mlx_get_data_addr(
			img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	cont->toggle_menu = false;
	cont->toggle_proj = false;
	reset_proportions(cont);
	return ;
}
