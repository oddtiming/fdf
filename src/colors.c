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

int	average_color(int color1, int color2, double percent)
{
	int	r;
	int	g;
	int	b;

	if (color1 == color2)
		return (color1);
	r = ((color2 >> 16 & 0xFF) - (color1 >> 16 & 0xFF)) * percent + (color1 >> 16 & 0xFF);
	g = ((color2 >> 8 & 0xFF) - (color1 >> 8 & 0xFF)) * percent + (color1 >> 8 & 0xFF);
	b = ((color2 & 0xFF) - (color1 & 0xFF)) * percent + (color1 & 0xFF);
	return ((r << 16) | (g << 8) | (b));
}