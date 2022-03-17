#include "fdf.h"

void	set_hooks(t_fdf_cont *cont)
{
	mlx_expose_hook(cont->win_ptr, handle_expose_hook, cont);
	mlx_key_hook(cont->win_ptr, handle_key_hook, cont);
	mlx_mouse_hook(cont->win_ptr, handle_mouse_hook, cont);
	mlx_loop_hook(cont->mlx_ptr, handle_default_hook, cont);
	mlx_hook(cont->win_ptr, DESTROY_NOTIFY, 0, fdf_clean_exit, cont);
	return ;
}

int	handle_default_hook(t_fdf_cont *cont)
{
	(void)cont;
	return (0);
}


int	handle_expose_hook(t_fdf_cont *cont)
{
	t_fdf_cont	*mlx;

	mlx = (t_fdf_cont *)cont;
	if (DEBUG)
	{
		printf("Expose_hook has been called! \n");
		printf("data_arrd = %p \n", cont->curr_img->data_addr);
		printf("img_ptr = %p \n", cont->curr_img->img_ptr);
		printf("bpp = %d \n", cont->curr_img->bpp);
		printf("line_len = %d \n", cont->curr_img->line_len);
		printf("endian = %d \n", cont->curr_img->endian);
	}
	return (0);
}

int	handle_key_hook(int keysym, t_fdf_cont *cont)
{
	t_fdf_cont	*mlx;

	mlx = (t_fdf_cont *)cont;
	if (DEBUG)
	{
		printf("Keysim = %d\n", keysym);
		printf("cont->curr_img->data_addr %p\n", cont->curr_img->data_addr);
		printf("cont->curr_img->bpp %d\n", cont->curr_img->bpp);
		printf("cont->curr_img->line_len %d\n", cont->curr_img->line_len);
		printf("cont->curr_img->width %d\n", cont->curr_img->width);
		printf("cont->curr_img->height %d\n", cont->curr_img->height);
		printf("cont->height %d\n", cont->height);
		printf("cont->width %d\n", cont->width);
		printf("Keysim = %d\n", keysym);
	}
	if (keysym == 53)
	{
		fdf_cleanup(cont);
		exit(0);
	}
	if (keysym == 1)
	{
		display_square(mlx);
	}
	if (keysym == 2)
	{
		display_default(mlx);
	}
	if (keysym == 37)
	{
		test_display_lines(mlx);
	}
	if (keysym == 40)
	{
		void	*img_ptr;
		int		height;
		int		width;

		img_ptr = NULL;
		height = 0;
		width = 0;
		img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./extra_stuff_not_important/sexy_kermit.xpm", &width, &height);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img_ptr, 0, 0);
	}
	return (0);
}

int	handle_mouse_hook(int button, int x, int y, t_fdf_cont *cont)
{
	t_fdf_cont	*mlx;

	mlx = (t_fdf_cont *)cont;
	if (DEBUG)
	{
		printf("Mouse coordinates (X: %d, Y: %d)\n", x, y);
		printf("Button pressed: %d \n", button);

	}
	return (0);
}
