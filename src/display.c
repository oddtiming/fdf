#include "fdf.h"

int	display_default(t_fdf_cont *cont)
{
	t_img	*img;
	
	img = cont->display_img;
	mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img->img_ptr, 0, 0);

	return (0);
}

int	display_img(t_fdf_cont *cont, t_img *img)
{
	mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img->img_ptr, 0, 0);

	return (0);
}

int	display_square(t_fdf_cont *cont)
{
	t_img	*img;
	
	img = cont->display_img;
	
	// put_square(cont, img, 400);
	draw_square(img, 500);
	cont->display_img = img;
	mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img->img_ptr, 0, 0);

	printf("img_ptr = %p \n", img->img_ptr);
	printf("bpp = %d \n", img->bpp);
	printf("line_len = %d \n", img->line_len);
	printf("endian = %d \n", img->endian);
	printf("data_addr = %p \n", img->data_addr);
	return (0);
}
