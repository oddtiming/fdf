#include "fdf.h"

void	fdf_init(t_fdf_cont *cont, char *filepath)
{
	t_img	*img;

	cont->mlx_ptr = mlx_init();
	if (!cont->mlx_ptr)
		exit_on_err("mlx: mlx_init() error \n");
	cont->win_name = ft_get_last_token(filepath, '/');
	cont->win_ptr = mlx_new_window(cont->mlx_ptr, cont->win_w, cont->win_h, cont->win_name);
	if (!cont->win_ptr)
		exit_on_err("mlx: mlx_new_window() error \n");
	cont->img = malloc(sizeof(t_img));
	if (!cont->img)
		exit_on_err("fdf_init: malloc error \n");
	img = cont->img;
	img->img_ptr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->width = cont->win_w;
	img->height = cont->win_h;
	img->img_ptr = mlx_new_image(cont->mlx_ptr, img->width, img->height);
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	draw_background(cont->img, FDF_BLACK);
	cont->toggle_rot_x = false;
	cont->toggle_rot_y = false;
	cont->toggle_rot_z = false;
	cont->toggle_menu = false;
	cont->map_is_colored = true;
	cont->toggle_proj = false;
	cont->x_offset = 0;
	cont->y_offset = 0;
	// rotate_x(cont, -0.5236);
	// rotate_y(cont, -0.5236);
	cont->theta_x = 0.788;
	cont->theta_y = 0.788;
	cont->theta_z = 0.788;
	cont->z_divisor = 1.0F;
	return ;
}
