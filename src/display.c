#include "fdf.h"
#include <sys/time.h>

int	display_default(t_fdf_cont *cont)
{
	t_img	*img;
	
	img = cont->curr_img;
	mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img->img_ptr, 0, 0);

	return (0);
}

int	display_img(t_fdf_cont *cont, t_img *img)
{
	mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

void	test_display_lines(t_fdf_cont *cont)
{
	t_2d_point p0_0;
	t_2d_point p100_100;
	t_2d_point p1;
	t_2d_point p2;
	t_2d_point p3;
	t_2d_point p4;
	t_2d_point p5;
	t_2d_point p6;
	t_2d_point p7;
	t_2d_point p8;
	t_2d_point p9;

	p0_0.x = 0;
	p0_0.y = 0;
	p100_100.x = 100;
	p100_100.y = 100;
	p1.x = 100;
	p1.y = 200;
	p2.x = 500;
	p2.y = 1000;
	p3.x = 1000;
	p3.y = 500;
	p4.x = 650;
	p4.y = 300;
	p5.x = 640;
	p5.y = 512;
	p6.x = 1042;
	p6.y = 179;
	p7.x = 1094;
	p7.y = 120;
	p8.x = 1068;
	p8.y = 127;
	p9.x = 1087;
	p9.y = 170;
	draw_line_rainbow(cont->curr_img, p0_0, p100_100);
	draw_line_rainbow(cont->curr_img, p0_0, p1);
	draw_line_rainbow(cont->curr_img, p0_0, p2);
	draw_line_rainbow(cont->curr_img, p0_0, p3);
	draw_line_rainbow(cont->curr_img, p0_0, p4);
	draw_line_rainbow(cont->curr_img, p0_0, p5);
	draw_line_rainbow(cont->curr_img, p0_0, p6);
	draw_line_rainbow(cont->curr_img, p100_100, p1);
	draw_line_rainbow(cont->curr_img, p100_100, p2);
	draw_line_rainbow(cont->curr_img, p100_100, p3);
	draw_line_rainbow(cont->curr_img, p100_100, p4);
	draw_line_rainbow(cont->curr_img, p100_100, p5);
	draw_line_rainbow(cont->curr_img, p100_100, p6);
	draw_line_rainbow(cont->curr_img, p1, p2);
	draw_line_rainbow(cont->curr_img, p1, p3);
	draw_line_rainbow(cont->curr_img, p1, p4);
	draw_line_rainbow(cont->curr_img, p1, p5);
	draw_line_rainbow(cont->curr_img, p1, p6);
	draw_line_rainbow(cont->curr_img, p2, p3);
	draw_line_rainbow(cont->curr_img, p2, p4);
	draw_line_rainbow(cont->curr_img, p2, p5);
	draw_line_rainbow(cont->curr_img, p2, p6);
	draw_line_rainbow(cont->curr_img, p3, p4);
	draw_line_rainbow(cont->curr_img, p3, p5);
	draw_line_rainbow(cont->curr_img, p3, p6);
	draw_line_rainbow(cont->curr_img, p4, p5);
	draw_line_rainbow(cont->curr_img, p4, p6);
	draw_line_rainbow(cont->curr_img, p5, p6);
	draw_line_rainbow(cont->curr_img, p6, p7);
	draw_line_rainbow(cont->curr_img, p8, p9);
	display_default(cont);
	return ;
}

void	test_display_lines_multicolor(t_fdf_cont *cont)
{
	t_2d_point	p0_0;
	t_2d_point	p100_100;
	t_2d_point	p1;
	t_2d_point	p2;
	t_2d_point	p3;
	t_2d_point	p4;
	t_2d_point	p5;
	t_2d_point	p6;
	t_2d_point	p7;
	t_2d_point	p8;
	t_2d_point	p9;
	static int	offset;

	if (offset % 255 == 0)
		offset += 50;
	p0_0.x = 0;
	p0_0.y = 0;
	p100_100.x = 100;
	p100_100.y = 100;
	p1.x = 100;
	p1.y = 200;
	p2.x = 500;
	p2.y = 1000;
	p3.x = 1000;
	p3.y = 500;
	p4.x = 650;
	p4.y = 300;
	p5.x = 640;
	p5.y = 512;
	p6.x = 1042;
	p6.y = 179;
	p7.x = 1094;
	p7.y = 120;
	p8.x = 1068;
	p8.y = 127;
	p9.x = 1087;
	p9.y = 170;
	draw_line_rainbow_offset(cont->curr_img, p0_0, p100_100, offset);
	draw_line_rainbow_offset(cont->curr_img, p0_0, p1, offset);
	draw_line_rainbow_offset(cont->curr_img, p0_0, p2, offset);
	draw_line_rainbow_offset(cont->curr_img, p0_0, p3, offset);
	draw_line_rainbow_offset(cont->curr_img, p0_0, p4, offset);
	draw_line_rainbow_offset(cont->curr_img, p0_0, p5, offset);
	draw_line_rainbow_offset(cont->curr_img, p0_0, p6, offset);
	draw_line_rainbow_offset(cont->curr_img, p100_100, p1, offset);
	draw_line_rainbow_offset(cont->curr_img, p100_100, p2, offset);
	draw_line_rainbow_offset(cont->curr_img, p100_100, p3, offset);
	draw_line_rainbow_offset(cont->curr_img, p100_100, p4, offset);
	draw_line_rainbow_offset(cont->curr_img, p100_100, p5, offset);
	draw_line_rainbow_offset(cont->curr_img, p100_100, p6, offset);
	draw_line_rainbow_offset(cont->curr_img, p1, p2, offset);
	draw_line_rainbow_offset(cont->curr_img, p1, p3, offset);
	draw_line_rainbow_offset(cont->curr_img, p1, p4, offset);
	draw_line_rainbow_offset(cont->curr_img, p1, p5, offset);
	draw_line_rainbow_offset(cont->curr_img, p1, p6, offset);
	draw_line_rainbow_offset(cont->curr_img, p2, p3, offset);
	draw_line_rainbow_offset(cont->curr_img, p2, p4, offset);
	draw_line_rainbow_offset(cont->curr_img, p2, p5, offset);
	draw_line_rainbow_offset(cont->curr_img, p2, p6, offset);
	draw_line_rainbow_offset(cont->curr_img, p3, p4, offset);
	draw_line_rainbow_offset(cont->curr_img, p3, p5, offset);
	draw_line_rainbow_offset(cont->curr_img, p3, p6, offset);
	draw_line_rainbow_offset(cont->curr_img, p4, p5, offset);
	draw_line_rainbow_offset(cont->curr_img, p4, p6, offset);
	draw_line_rainbow_offset(cont->curr_img, p5, p6, offset);
	draw_line_rainbow_offset(cont->curr_img, p6, p7, offset);
	draw_line_rainbow_offset(cont->curr_img, p8, p9, offset);
	display_default(cont);
	offset += 5;
	return ;
}

int	display_square_rainbow(t_fdf_cont *cont)
{
	t_img	*img;
	
	img = cont->curr_img;
	
	for (int i = 0; i < 100; i++)
	{
		draw_square_rainbow(img, 500);
		cont->curr_img = img;
		mlx_put_image_to_window(cont->mlx_ptr, cont->win_ptr, img->img_ptr, 0, 0);
	}

	return (0);
}