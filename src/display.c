/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:07:47 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/16 16:08:00 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	display_default(t_fdf_cont *cont)
{
	t_img	*img;

	img = cont->img;
	mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

int	display_img(t_fdf_cont *cont, void *img_ptr)
{
	mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img_ptr, 0, 0);
	return (0);
}
