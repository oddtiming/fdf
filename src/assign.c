#include "fdf.h"

void	assign_limits(t_fdf_cont *cont)
{
	int	x;
	int	y;

	cont->max_alt = 0;
	cont->min_alt = 0;
	y = 0;
	while (y < cont->map_height)
	{
		x = 0;
		while (x < cont->map_width)
		{
			if (cont->map[x + y * cont->map_width].z < cont->min_alt)
				cont->min_alt = cont->map[x + y * cont->map_width].z;
			else if (cont->map[x + y * cont->map_height].z > cont->max_alt)
				cont->max_alt = cont->map[x + y * cont->map_width].z;
			x++;
		}
		y++;
	}
	cont->square_width = 5;
	if (ft_max(cont->map_height, cont->map_width) < 100)
		cont->square_width = ft_min(20, ft_max(683 / cont->map_height, 853 / cont->map_width));
	if (DEBUG)
		printf("square_width = %d\n", cont->square_width);
	cont->win_height = cont->map_height * cont->square_width * 3;
	cont->win_width = cont->map_width * cont->square_width * 3;
	if (cont->win_width < 300)
		cont->win_width = 300;
	else if (cont->win_width > 1280)
		cont->win_width = 1280;
	if (cont->win_height < 300)
		cont->win_height = 300;
	else if (cont->win_height > 1024)
		cont->win_height = 1024;
}

void	assign_map_line(t_fdf_cont *cont, char *line, int y)
{
	t_point	*point;
	int		index;
	int		x;

	index = 0;
	x = 0;
	while (x < cont->map_width)
	{
		point = &cont->map[x + (y * cont->map_width)];
		point->x = x;
		point->y = y;
		point->z = ft_atoi(&line[index]);
		while (ft_isspace(line[index]))
			index++;
		while (ft_isdigit(line[index]))
			index++;
		if (line[index] == ',' || line[index] == '.')
			point->color = ft_atox(&line[++index]);
		else
			point->color = FDF_WHITE;
		while (is_set(line[index], "0123456789ABCDEFabcdefx"))
			index++;
		x++;
	}
}

void	assign_map(t_fdf_cont *cont, int fd)
{
	char	*curr_line;
	int		y;

	cont->map = malloc(cont->map_width * cont->map_height * sizeof(t_point));
	if (!cont->map)
		exit_on_err("assign_map: malloc error \n");
	y = 0;
	while (y < cont->map_height)
	{
		curr_line = get_next_line(fd);
		assign_map_line(cont, curr_line, y);
		free(curr_line);
		y++;
	}
	while (curr_line)
		curr_line = get_next_line(fd);
	if (DEBUG)
	{
		print_map(cont);
	}
	return ;
}

//If z is negative, go from 0xFFFFFF to 0x00FFFF at median, and 0x0000FF at max_alt
//If z is positive, go from 0xFFFFFF to 0xFFFF00 at median, and 0xFF00FF at max_alt
void	assign_colors(t_fdf_cont *cont)
{
	double	altitude_percent;
	int		curr_color;
	int		x;
	int		y;

	y = 0;
	while (y < cont->map_height)
	{
		x = 0;
		while (x < cont->map_width)
		{
			
			if (cont->map[x + y * cont->map_width].z == 0)
			{
				cont->map[x + y * cont->map_width].color = FDF_WHITE;
				x++;
				continue;
			}
			else if (cont->map[x + y * cont->map_width].z > 0)
				altitude_percent = cont->map[x + y * cont->map_width].z / cont->max_alt;
			else
				altitude_percent = cont->map[x + y * cont->map_width].z / cont->min_alt;
			if (cont->map[x + y * cont->map_width].z > 0)
				curr_color = average_color(0, 0xFF0000, altitude_percent);
			else
				curr_color = average_color(0, 0xFF, altitude_percent);
			cont->map[x + y * cont->map_width].color = curr_color;
			x++;
		}
		y++;
	}
	return ;
}
