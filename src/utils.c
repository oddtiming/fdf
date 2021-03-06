#include "fdf.h"

void	*ft_safealloc(size_t size)
{
	void	*mem_space;

	mem_space = malloc(size);
	if (!mem_space)
	{
		write(STDERR_FILENO, "Malloc Error\n", 13);
		exit (EXIT_FAILURE);
	}
	return (mem_space);
}

double	linear_interpolation(double start, double end, double curr)
{
	if (curr == start || end == start)
		return (0.0F);
	else if (curr == end)
		return (1.0F);
	return ((curr - start) / (end - start));
}

void	draw_background(t_img *img, int color)
{
	ft_memset(img->data_addr, color, img->line_len * img->height);
}

void	fill_pixel(t_img *img, int x, int y, int color)
{
	char	*cast_ptr;

	if (!img)
		exit_on_err("fill_pixel: img does not exist\n");
	else if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	cast_ptr = (char *)(img->data_addr + x * img->bpp / 8 + y * img->line_len);
	*(int *)cast_ptr = color;
}
