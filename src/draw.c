#include "fdf.h"

void	put_square(t_mlx *mlx, t_img *img, int size)
{
	int	half_length;
	int	x;
	int	y;

	half_length = size / 2;
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

int	draw_square(t_mlx *mlx)
{
	char	*data_addr;
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
	data_addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->size_line, &img->endian);
	
	put_square(mlx, img, 400);
	// mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img, 0, 0);

	printf("img_ptr = %p \n", img->img_ptr);
	printf("bits_per_pixel = %d \n", img->bits_per_pixel);
	printf("size_line = %d \n", img->size_line);
	printf("endian = %d \n", img->endian);
	printf("data_addr = %p \n", data_addr);
	return (0);
}