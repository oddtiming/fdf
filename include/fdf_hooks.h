/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismaelyahyaouiracine <ismaelyahyaouirac    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:07:15 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/10/19 20:22:03 by ismaelyahya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_HOOKS_H
# define FDF_HOOKS_H
/**
 *	This header is for the hooks family of c files
 *		hooks.c
 *		key_hooks.c
 *		mouse_hooks.c
 */

# define TWO_PI 6.28318530718

typedef struct s_fdf	t_fdf;
typedef enum e_keyhooks
{
	KEY_0 = 29,
	KEY_1 = 18,
	KEY_2 = 19,
	KEY_3 = 20,
	KEY_4 = 21,
	KEY_5 = 23,
	KEY_6 = 22,
	KEY_7 = 26,
	KEY_8 = 28,
	KEY_9 = 25,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_PLUS = 24,
	KEY_MINUS = 27,
	KEY_A = 0,
	KEY_B = 11,
	KEY_C = 8,
	KEY_D = 2,
	KEY_E = 14,
	KEY_F = 3,
	KEY_G = 5,
	KEY_H = 4,
	KEY_I = 34,
	KEY_J = 38,
	KEY_K = 40,
	KEY_L = 37,
	KEY_M = 46,
	KEY_N = 45,
	KEY_O = 31,
	KEY_P = 35,
	KEY_Q = 12,
	KEY_R = 15,
	KEY_S = 1,
	KEY_T = 17,
	KEY_U = 32,
	KEY_V = 9,
	KEY_W = 13,
	KEY_X = 7,
	KEY_Y = 16,
	KEY_Z = 6,
	KEY_ESC = 53,
	KEY_F1 = 122,
	NUMPAD0 = 82,
	NUMPAD1 = 83,
	NUMPAD2 = 84,
	NUMPAD3 = 85,
	NUMPAD4 = 86,
	NUMPAD6 = 88,
	NUMPAD5 = 87,
	NUMPAD7 = 89,
	NUMPAD8 = 91,
	NUMPAD9 = 92,
	NUMPAD_MINUS = 78,
	NUMPAD_PLUS = 69
}	t_keyhooks;

typedef enum e_mlx_events
{
	KEYPRESS = 2,
	MOTION_NOTIFY = 6,
	DESTROY_NOTIFY = 17
}	t_mlx_events;

//FUNCTIONS
int		handle_expose_hook(t_fdf *cont);
int		handle_key_release_hook(int keysym, t_fdf *cont);
int		handle_key_press_hook(int keysym, t_fdf *cont);
int		handle_key_press_hook_2(int keysym, t_fdf *cont);
int		handle_mouse_hook(int button, int x, int y, t_fdf *cont);
int		handle_mouse_motion(int x, int y, t_fdf *cont);
int		default_hook(t_fdf *cont);

#endif