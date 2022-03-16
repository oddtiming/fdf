#include "fdf.h"

// void	draw_line(t_img *img, t_2d_point p1, t_2d_point p2)
// {
// 	int	diff_x;
// 	int	diff_y;


// 	diff_x = (int)fabs(p1.x - p2.x);
// 	diff_y = (int)fabs(p1.y - p2.y);

// }

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
