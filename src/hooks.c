/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:07:26 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/16 16:08:00 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	mlx_hook(cont->win_ptr, KEYPRESS, 1L << 0, handle_key_press_hook, cont);
	mlx_hook(cont->win_ptr, MOTION_NOTIFY, 1L << 3, handle_mouse_motion, cont);
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
