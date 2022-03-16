#include "fdf.h"

void	fill_pixel(t_img *img, int x, int y, int color)
{
	void	*cast_ptr;

	cast_ptr = (void *)(img->data_addr + x * img->bpp / 8 + y * img->line_len);
	*(int *)cast_ptr = color;
}

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
