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
