#include "fdf.h"

int	display_default(t_fdf *cont)
{
	t_img	*img;

	img = cont->img;
	mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

int	display_img(t_fdf *cont, void *img_ptr)
{
	mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img_ptr, 0, 0);
	return (0);
}
