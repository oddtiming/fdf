#include "fdf.h"

int	fdf_clean_exit(t_fdf_cont *cont)
{
	fdf_cleanup(cont);
	exit(EXIT_SUCCESS);
}

void	fdf_cleanup(t_fdf_cont *cont)
{
	mlx_destroy_window(cont->mlx_ptr, cont->win_ptr);
	mlx_destroy_image(cont->mlx_ptr, cont->curr_img->img_ptr);
	free(cont->map);
	free(cont->curr_img);
	free(cont);
	return ;
}