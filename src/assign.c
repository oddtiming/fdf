#include "fdf.h"

static void	assign_notable_altitudes(t_fdf *cont)
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
	return ;
}

static void	assign_window_dimensions(t_fdf *cont)
{
	cont->win_h = WIN_H;
	cont->win_w = WIN_W;
	// cont->win_h = cont->map_h * cont->square_width * 3;
	// cont->win_w = cont->map_w * cont->square_width * 3;
	// if (cont->win_w < 300)
	// 	cont->win_w = 300;
	// else if (cont->win_w > 1280)
	// 	cont->win_w = 1280;
	// if (cont->win_h < 300)
	// 	cont->win_h = 300;
	// else if (cont->win_h > 1024)
	// 	cont->win_h = 1024;
}

void	assign_limits(t_fdf *cont)
{
	assign_notable_altitudes(cont);
	cont->square_width = 5;
	if (ft_max(cont->map_h, cont->map_w) < 60)
		cont->square_width = ft_min(20,
				ft_max(683 / cont->map_h, 853 / cont->map_w));
	assign_window_dimensions(cont);
}

static void	assign_map_line(t_fdf *cont, char *line, int y)
{
	t_point	*point;
	int		index;
	int		x;

	index = 0;
	x = -1;
	while (++x < cont->map_w)
	{
		point = &cont->map[x + (y * cont->map_w)];
		point->x = x;
		point->y = y;
		point->z = ft_atoi(&line[index]);
		while (ft_isspace(line[index]))
			index++;
		while (line[index] == '-' || ft_isdigit(line[index]))
			index++;
		point->color = WHITE;
		if (line[index] == ',' || line[index] == '.')
		{
			point->color = ft_atox(&line[++index]);
			cont->map_is_colored = true;
		}
		while (is_set(line[index], "0123456789ABCDEFabcdefx"))
			index++;
	}
}

void	assign_map(t_fdf *cont, int fd)
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
