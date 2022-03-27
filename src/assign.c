#include "fdf.h"

void	assign_limits(t_fdf_cont *cont)
{
	int	x;
	int	y;

	cont->max_alt = 0;
	cont->min_alt = 0;
	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			if (cont->map[x + y * cont->map_w].z < cont->min_alt)
				cont->min_alt = cont->map[x + y * cont->map_w].z;
			else if (cont->map[x + y * cont->map_h].z > cont->max_alt)
				cont->max_alt = cont->map[x + y * cont->map_w].z;
			x++;
		}
		y++;
	}
	cont->square_width = 5;
	if (ft_max(cont->map_h, cont->map_w) < 60)
		cont->square_width = ft_min(20, ft_max(683 / cont->map_h, 853 / cont->map_w));
	cont->win_h = cont->map_h * cont->square_width * 3;
	cont->win_w = cont->map_w * cont->square_width * 3;
	if (cont->win_w < 300)
		cont->win_w = 300;
	else if (cont->win_w > 1280)
		cont->win_w = 1280;
	if (cont->win_h < 300)
		cont->win_h = 300;
	else if (cont->win_h > 1024)
		cont->win_h = 1024;
	//todo: will become useful when rotation is calculated at projection
	// if (ft_max(cont->max_alt, abs(cont->min_alt)) > ft_max(cont->map_h, cont->map_w) / 3)
	// {
	// 	cont->z_divisor = 0.25F;
	// 	cont->max_alt /= 4.0F;
	// 	cont->min_alt /= 4.0F;
	// }
}

void	assign_map_line(t_fdf_cont *cont, char *line, int y)
{
	t_point	*point;
	int		index;
	int		x;

	index = 0;
	x = 0;
	while (x < cont->map_w)
	{
		point = &cont->map[x + (y * cont->map_w)];
		point->x = x;
		point->y = y;
		point->z = -ft_atoi(&line[index]);
		while (ft_isspace(line[index]))
			index++;
		if (line[index] == '-')
			index++;
		while (ft_isdigit(line[index]))
			index++;
		point->color = FDF_WHITE;
		if (line[index] == ',' || line[index] == '.')
		{
			point->color = ft_atox(&line[++index]);
			cont->map_is_colored = true;
		}
		while (is_set(line[index], "0123456789ABCDEFabcdefx"))
			index++;
		x++;
	}
}

void	assign_map(t_fdf_cont *cont, int fd)
{
	char	*curr_line;
	int		y;

	cont->map = malloc(cont->map_w * cont->map_h * sizeof(t_point));
	if (!cont->map)
		exit_on_err("assign_map: malloc error \n");
	y = 0;
	while (y < cont->map_h)
	{
		curr_line = get_next_line(fd);
		assign_map_line(cont, curr_line, y);
		free(curr_line);
		y++;
	}
	while (curr_line)
		curr_line = get_next_line(fd);
	return ;
}

void	assign_point_color(t_fdf_cont *cont, int x, int y)
{
	double	curr_alt;
	double	median_max;
	double	median_min;
	int		curr_color;

	curr_alt = cont->map[x + y * cont->map_w].z;
	median_max = cont->max_alt / 2;
	median_min = cont->min_alt / 2;
	curr_color = FDF_WHITE;
	if (curr_alt > 0)
	{
		curr_color = average_color(FDF_YELLOW, FDF_RED, curr_alt / median_max);
		if (curr_alt > median_max)
			curr_color = average_color(FDF_RED, FDF_PINK, \
				linear_interpolation(median_max, cont->max_alt, curr_alt));
	}
	else if (curr_alt < 0)
	{
		curr_color = average_color(FDF_YELLOW, FDF_BLUE, curr_alt / median_min);
		if (curr_alt < median_min)
			curr_color = average_color(FDF_BLUE, FDF_CYAN, \
				linear_interpolation(median_min, cont->min_alt, curr_alt));
	}
	cont->map[x + y * cont->map_w].color = curr_color;
}

//If z is negative, go from 0xFFFFFF to 0x00FFFF at median, and 0x0000FF at max_alt
//If z is positive, go from 0xFFFFFF to 0xFFFF00 at median, and 0xFF00FF at max_alt
void	assign_colors(t_fdf_cont *cont)
{
	int		x;
	int		y;

	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			assign_point_color(cont, x, y);
			x++;
		}
		y++;
	}
	return ;
}
