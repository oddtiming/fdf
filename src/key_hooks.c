/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:07:29 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/16 16:08:00 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_hooks.h"

static void	toggle_all_rotations(t_fdf_cont *cont)
{
	cont->toggle_rot_x = !cont->toggle_rot_x;
	cont->toggle_rot_y = !cont->toggle_rot_y;
	cont->toggle_rot_z = !cont->toggle_rot_z;
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
		toggle_all_rotations(cont);
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
	if (keysym == NUMPAD_PLUS || keysym == KEY_PLUS)
		if (cont->square_width < 150)
			cont->square_width += 1;
	if (keysym == NUMPAD_MINUS || keysym == KEY_MINUS)
		if (cont->square_width > 2)
			cont->square_width -= 1;
	if (keysym == NUMPAD7)
		cont->theta_z -= 0.1;
	if (keysym == NUMPAD8)
		cont->theta_z += 0.1;
	if (keysym == NUMPAD4)
		cont->theta_y -= 0.1;
	if (keysym == NUMPAD5)
		cont->theta_y += 0.1;
	if (keysym == NUMPAD1)
		cont->theta_x -= 0.1;
	if (keysym == NUMPAD2)
		cont->theta_x += 0.1;
	if (cont->toggle_proj && keysym == KEY_O)
		cycle_orthographic_perspectives(cont);
	return (handle_key_press_hook_2(keysym, cont));
}

int	handle_key_press_hook_2(int keysym, t_fdf_cont *cont)
{
	if (keysym == KEY_W)
		if (cont->z_offset > -1000)
			cont->z_offset -= 8;
	if (keysym == KEY_S)
		if (cont->z_offset < 2000)
			cont->z_offset += 8;
	if (keysym == KEY_Q)
		if (cont->z_divisor > -5)
			cont->z_divisor -= 0.12;
	if (keysym == KEY_E)
		if (cont->z_divisor < 5)
			cont->z_divisor += 0.12;
	if (keysym == KEY_LEFT || keysym == KEY_A)
		if (cont->x_offset < cont->win_w * 0.1F * cont->square_width)
			cont->x_offset += 10;
	if (keysym == KEY_RIGHT || keysym == KEY_D)
		if (cont->x_offset > cont->win_w * -0.1F * cont->square_width)
			cont->x_offset -= 10;
	if (keysym == KEY_UP || keysym == KEY_Z)
		if (cont->y_offset < cont->win_h * 0.1F * cont->square_width)
			cont->y_offset += 10;
	if (keysym == KEY_DOWN || keysym == KEY_X)
		if (cont->y_offset > cont->win_h * -0.1F * cont->square_width)
			cont->y_offset -= 10;
	return (0);
}
