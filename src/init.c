#include "fdf.h"

int	init_fdf(t_fdf_cont *cont, char *map_name)
{
	cont->mlx_ptr = mlx_init();
	if (!cont->mlx_ptr)
		return (EXIT_FAILURE);
	cont->win_ptr = mlx_new_window(cont->mlx_ptr, cont->width, cont->height, map_name);
	cont->display_img = NULL;
	return (0);
}