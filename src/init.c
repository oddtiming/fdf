#include "fdf.h"

int	init_fdf(t_fdf_cont *cont, char *map_name)
{
	t_img *img;

	cont->mlx_ptr = mlx_init();
	if (!cont->mlx_ptr)
		return (EXIT_FAILURE);
	cont->win_ptr = mlx_new_window(cont->mlx_ptr, cont->width, cont->height, map_name);
	cont->display_img = malloc(sizeof(t_img));
	img = cont->display_img;
	if (!img)
		return (EXIT_FAILURE);
	img->img_ptr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->width = WIN_W;
	img->height = WIN_H;
	img->img_ptr = mlx_new_image(cont->mlx_ptr, img->width, img->height);
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	return (0);
}