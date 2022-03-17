#include "fdf.h"

void	fill_pixel(t_img *img, int x, int y, int color)
{
	void	*cast_ptr;

	if (!img)
		exit_on_err("fill_pixel: img does not exist\n");
	else if (x < 0 || x > img->width || y < 0 || y > img->height)
		exit_on_err("fill_pixel: out of bounds coordinates\n");
	cast_ptr = (void *)(img->data_addr + x * img->bpp / 8 + y * img->line_len);
	*(int *)cast_ptr = color;
}
