#include "fdf.h"

void	fill_square_img_row(t_img *img, int size, int y, int color)
{
	int height;
	int width;
	int	x;

	height = img->height;
	width = img->width;
	x = 0;
	while (x < width)
	{
		// fill_pixel(img, x, y, FDF_BLACK);
		if (x >= width / 2 - size / 2 && x <= width / 2 + size / 2 && \
			y >= height / 2 - size / 2 && y <= height / 2 + size / 2)
			fill_pixel(img, x, y, color);
		else
			fill_pixel(img, x, y, 0);
		x++;
	}
}

void	draw_square(t_img *img, int size)
{
	int	y;

	y = 0;
	while (y < img->height)
	{
		fill_square_img_row(img, size, y, FDF_WHITE);
		y++;
	}
	return ;
}

void	put_square(t_fdf_cont *cont, t_img *img, int size)
{
	int	half_length;
	int	*map;
	int	x;
	int	y;

	half_length = size / 2;
	map = malloc (size * (size * sizeof(int)));
	y = img->height / 2 - half_length;
	while (y < img->height / 2 + half_length)
	{
		x = img->height / 2 - half_length;
		while (x < img->width / 2 + half_length)
		{
			mlx_pixel_put(cont->mlx_ptr, cont->win_ptr, x, y, FDF_WHITE);
			x++;
		}
		y++;
	}
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
