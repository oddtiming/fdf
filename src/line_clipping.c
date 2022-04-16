/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_clipping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:07:38 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/16 16:08:00 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	line_clip_p1(t_fdf_cont *cont, t_point *p1, t_point *p2)
{
	int	max_w;

	max_w = cont->win_w - 1;
	if (p1->x < 0)
	{
		p1->y += linear_interpolation(p1->x, p2->x, 0) * (p2->y - p1->y);
		p1->x = 0;
	}
	else if (p1->x > cont->win_w - 1)
	{
		p1->y += linear_interpolation(p1->x, p2->x, max_w) * (p2->y - p1->y);
		p1->x = cont->win_w - 1;
	}
	else if (p2->x < 0)
	{
		p2->y += linear_interpolation(p2->x, p1->x, 0) * (p1->y - p2->y);
		p2->x = 0;
	}
	else if (p2->x > cont->win_w - 1)
	{
		p2->y += linear_interpolation(p2->x, p1->x, max_w) * (p1->y - p2->y);
		p2->x = cont->win_w - 1;
	}
}

static void	line_clip_p2(t_fdf_cont *cont, t_point *p1, t_point *p2)
{
	int	max_h;

	max_h = cont->win_h - 1;
	if (p1->y < 0)
	{
		p1->x += linear_interpolation(p1->y, p2->y, 0) * (p2->x - p1->x);
		p1->y = 0;
	}
	else if (p1->y > cont->win_h - 1)
	{
		p1->x += linear_interpolation(p1->y, p2->y, max_h) * (p2->x - p1->x);
		p1->y = cont->win_h - 1;
	}
	else if (p2->y < 0)
	{
		p2->x += linear_interpolation(p2->y, p1->y, 0) * (p1->x - p2->x);
		p2->y = 0;
	}
	else if (p2->y > cont->win_h - 1)
	{
		p2->x += linear_interpolation(p2->y, p1->y, max_h) * (p1->x - p2->x);
		p2->y = cont->win_h - 1;
	}
}

int	line_clipping(t_fdf_cont *cont, t_point *p1, t_point *p2)
{
	if (!cont->toggle_proj && (p1->z <= 0 || p2->z <= 0))
		return (EXIT_FAILURE);
	if ((p1->x >= 0 && p1->x <= cont->win_w && \
		p1->y >= 0 && p1->y <= cont->win_h) && \
		(p2->x >= 0 && p2->x <= cont->win_w && \
		p2->y >= 0 && p2->y <= cont->win_h))
		return (EXIT_SUCCESS);
	line_clip_p1(cont, p1, p2);
	line_clip_p2(cont, p1, p2);
	if ((p1->x < 0 || p1->x > cont->win_w - 1 || \
		p1->y < 0 || p1->y > cont->win_h - 1) || \
		(p2->x < 0 || p2->x > cont->win_w - 1 || \
		p2->y < 0 || p2->y > cont->win_h - 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
