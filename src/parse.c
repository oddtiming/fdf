#include "fdf.h"

int	ft_isspace(int c)
{
	return ((c > 8 && c < 14) || c == 32);
}

int	fdf_pos(int x, int y)
{
	return (x + y * )
}

int	parse_map_line(char *curr_line)
{
	int		curr_line_width;
	int		i;

	i = 0;
	while (curr_line[i])
	{
		curr_line_width = 0;
		while (ft_isspace(curr_line[i]))
			i++;
		if (ft_isdigit(curr_line[i]))
		{
			curr_line_width++;
			while (ft_isdigit(curr_line[i]))
				i++;
		}
		if (!ft_isspace(curr_line[i]) && curr_line[i] != 0)
			exit_on_err("Map error: one of the inputs is not an int\n");
	}
	return (curr_line_width);
}

void	parse_map_dimensions(t_fdf_cont *cont, int fd)
{
	char	*curr_line;
	int		curr_line_width;

	cont->map_height = 0;
	cont->map_width = 0;
	curr_line = get_next_line(fd);
	while (curr_line)
	{
		curr_line_width = parse_map_line(curr_line);
		if (cont->map_width == 0)
			cont->map_width = curr_line_width;
		else if (cont->map_width != curr_line_width)
			exit_on_err("Map error: map is not rectangular\n")
		free (curr_line);
		get_next_line(fd);
		map->map_height++;
	}
	close (fd);
	return ;
}

void	assign_points_to_map(t_fdf_cont *cont, int fd)
{
	char	*curr_line;
	int		curr_x;
	int		curr_y;
	int		i;

	cont->map = malloc(cont->map_width * cont->map_height * sizeof(t_point));
	if (!cont->map)
		exit_on_err("assign_points_to_map: malloc error \n");
	curr_line = get_next_line(fd);
	curr_y = 0;
	while (curr_y < cont->map_height)
	{
		curr_x = 0;
		while (curr_x < cont->map_width)
		{
			cont->map[curr_x + curr_y * map->map_height].x = curr_x;
			cont->map[curr_x + curr_y * map->map_height].y = curr_y;
			cont->map[curr_x + curr_y * map->map_height].z = ft_atoi(curr_line[i]);
			while (ft_isspace(curr_line[i]))
				i++;
			while (ft_isdigit(curr_line[i]))
				i++;
			curr_x++;
		}
		free(curr_line);
		curr_line = get_next_line(fd);
		curr_y++;
	}
	return ;
}

void	fdf_parse(t_fdf_cont *cont, char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit_on_err("input file error\n");
	parse_map_dimensions(cont, fd);
	fd = open(filepath, O_RDONLY);
	assign_points_to_map(cont, fd);
	close(fd);
	return ;
}