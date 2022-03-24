#include "fdf.h"

void	change_color_offset(int x, int y, int *color, int offset)
{
	int	red;
	int	green;
	int	blue;
	
	red = ((x + offset) % (offset % 1023)) >> 1;
	green = (abs(x - y) % (offset % 1023)) >> 1;
	blue = ((y + offset) % (offset % 1023)) >> 1;
	*color = (red << 16) + (green << 8) + blue;
}

void	change_color(int x, int y, int *color)
{
	int	red;
	int	green;
	int	blue;

	red = x >> 2;
	green = (x + y) >> 1;
	blue = y >> 2;
	*color = (red << 16) + (green << 8) + blue;
}

//If z is negative, go from 0xFFFFFF to 0x00FFFF at median, and 0x0000FF at max_alt
//If z is positive, go from 0xFFFFFF to 0xFFFF00 at median, and 0xFF00FF at max_alt
void	fdf_assign_map_colors(t_fdf_cont *cont)
{
	int	r;
	int	g;
	int	b;
	int	x;
	int	y;

	r = 0xFF;
	y = 0;
	while (y < cont->map_height)
	{
		x = 0;
		while (x < cont->map_width)
		{
			g = 255 - fabs(cont->map[x + y * cont->map_width].z) / 10 * 255;
			b = 255 - fabs(cont->map[x + y * cont->map_width].z) / 10 * 255;
			cont->map[x + y * cont->map_width].color = r << 16 | g << 8 | b;
			x++;
		}
		y++;
	}

}
