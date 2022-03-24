#include "fdf.h"

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

int	is_valid_input(const char *input)
{
	int	index;

	index = 0;
	while (ft_isspace(input[index]))
		index++;
	if (input[index] == '-')
		index++;
	if (ft_isdigit(input[index]))
	{
		while (ft_isdigit(input[index]))
			index++;
		if (input[index] == ',')
			index++;
		while (ft_isdigit(input[index]))
			index++;
		if (input[index] == 'x')
			index++;
		while (is_set(input[index], "0123456789ABCDEFabcdef"))
			index++;
	}
	else
		return (0);
	if (!ft_isspace(input[index]) && input[index] != 0)
		return (0);
	return (index);
}

int	parse_map_line(char *curr_line)
{
	int		curr_line_width;
	int		index;
	int		prev_i;

	index = 0;
	curr_line_width = 0;
	while (curr_line[index])
	{
		prev_i = index;
		index += is_valid_input(&curr_line[index]);
		if (prev_i != index)
			curr_line_width++;
		else
			return (0);
		while (ft_isspace(curr_line[index]))
			index++;
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
		if (curr_line_width == 0)
			exit_on_err("Map error: one of the inputs is not an int\n");
		else if (cont->map_width == 0)
			cont->map_width = curr_line_width;
		else if (cont->map_width != curr_line_width)
			exit_on_err("Map error: map is not rectangular\n");
		cont->map_height += 1;
		free(curr_line);
		curr_line = get_next_line(fd);
	}
	close (fd);
	return ;
}

void	assign_map_line(t_fdf_cont *cont, char *curr_line, int y)
{
	int		index;
	int		x;

	index = 0;
	x = 0;
	while (x < cont->map_width)
	{
		cont->map[x + (y * cont->map_width)].x = x;
		cont->map[x + (y * cont->map_width)].y = y;
		cont->map[x + (y * cont->map_width)].z = ft_atoi(&curr_line[index]);
		while (ft_isspace(curr_line[index]))
			index++;
		while (ft_isdigit(curr_line[index]))
			index++;
		x++;
	}
}

void	assign_points_to_map(t_fdf_cont *cont, int fd)
{
	char	*curr_line;
	int		y;

	cont->map = malloc(cont->map_width * cont->map_height * sizeof(t_point));
	if (!cont->map)
		exit_on_err("assign_points_to_map: malloc error \n");
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
