#include "fdf.h"

void	fill_pixel(t_img *img, int x, int y, int color)
{
	void	*cast_ptr;

	cast_ptr = (void *)(img->data_addr + x * img->bpp / 8 + y * img->line_len);
	*(int *)cast_ptr = color;
}
