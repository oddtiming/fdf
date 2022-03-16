#include "fdf.h"

void	do_mlx_loop(void *mlx_ptr)
{
	mlx_loop(mlx_ptr);
}

int	main(void)
{
	t_fdf_cont	*cont;
	char		*title = "open_window_test";

	cont = malloc(sizeof(t_fdf_cont));
	if (!cont)
		exit(1);
	cont->height = WIN_H;
	cont->width = WIN_W;
	if (init_fdf(cont, title))
		return (0);

	display_square(cont);


	printf("im main: img_ptr = %p \n", cont->display_img->img_ptr);
	printf("im main: bpp = %d \n", cont->display_img->bpp);
	printf("im main: line_len = %d \n", cont->display_img->line_len);
	printf("im main: endian = %d \n", cont->display_img->endian);
	printf("im main: data_addr = %p \n", cont->display_img->data_addr);

	set_hooks(cont);
	do_mlx_loop(cont->mlx_ptr);

	// free(mlx_ptr);
	fdf_cleanup(cont);
	return (0);
}


//Tutorial : https://www.youtube.com/c/BrendanGalea/videos