#include "fdf.h"

void	fdf_init(t_fdf_cont *cont, char *filepath)
{
	t_img	*img;

	cont->mlx_ptr = mlx_init();
	if (!cont->mlx_ptr)
		exit_on_err("mlx: mlx_init() error \n");
	cont->win_name = ft_get_last_token(filepath, '/');
	cont->win_ptr = mlx_new_window(cont->mlx_ptr, WIN_W, WIN_H, cont->win_name);
	if (!cont->win_ptr)
		exit_on_err("mlx: mlx_new_window() error \n");
	cont->curr_img = malloc(sizeof(t_img));
	img = cont->curr_img;
	if (!img)
		exit_on_err("fdf_init: malloc error \n");
	img->img_ptr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->width = WIN_W;
	img->height = WIN_H;
	img->img_ptr = mlx_new_image(cont->mlx_ptr, img->width, img->height);
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	draw_background(cont->curr_img, FDF_BLACK);
	return ;
}
