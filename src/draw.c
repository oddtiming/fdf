#include "fdf.h"

void	fill_square(t_img *img, int size)
{
	void	*cast_ptr;
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			cast_ptr = (void *)(img->data_addr + (x * 4 + y * img->size_line));
			*(int *)cast_ptr = 0x0;
			if (x >= img->height / 2 - size / 2 && x <= img->width / 2 + size / 2 && \
				y >= img->height / 2 - size / 2 && y <= img->width / 2 + size / 2)
				*(int *)cast_ptr = 0xFF00FF;
			x++;
		}
		y++;
	}
	return ;
}

void	put_square(t_fdf_cont *mlx, t_img *img, int size)
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
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

int	display_square(t_fdf_cont *mlx)
{
	t_img	*img;
	
	img = malloc(sizeof(t_img));
	if (!img)
		exit (1);
	img->img_ptr = NULL;
	img->bits_per_pixel = 0;
	img->size_line = 0;
	img->endian = 0;
	img->width = 800;
	img->height = 800;
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, img->width, img->height);
	img->data_addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->size_line, &img->endian);
	
	// put_square(mlx, img, 400);
	fill_square(img, 500);
	mlx->display_img = img;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img->img_ptr, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, img->img_ptr);
	free(img);

	printf("img_ptr = %p \n", img->img_ptr);
	printf("bits_per_pixel = %d \n", img->bits_per_pixel);
	printf("size_line = %d \n", img->size_line);
	printf("endian = %d \n", img->endian);
	printf("data_addr = %p \n", img->data_addr);
	return (0);
}