#include "fdf.h"

void	fdf_parse(t_fdf_cont *cont, char *filepath)
{
	char	*file_extension;
	int		fd;

	file_extension = ft_strrchr(filepath, '.');
	if (!file_extension || ft_strcmp(file_extension, ".fdf"))
		exit_on_err("Input file needs to be a .fdf file \n");
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit_on_err("Input file cannot be opened \n");
	parse_map(cont, fd);
	fd = open(filepath, O_RDONLY);
	assign_map(cont, fd);
	assign_limits(cont);
	if (DEBUG)
	{
		printf("cont->max_alt = %d \n", cont->max_alt);
		printf("cont->min_alt = %d \n", cont->min_alt);
		printf("cont->square_width = %d \n", cont->square_width);
		printf("cont->win_w = %d \n", cont->win_w);
		printf("cont->win_h = %d \n", cont->win_h);
	}

	if (cont->map_is_colored == false)
		assign_colors(cont);
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

int	parse_map_line(char *line)
{
	int		curr_line_width;
	int		index;
	int		prev_i;

	index = 0;
	curr_line_width = 0;
	while (line[index])
	{
		while (ft_isspace(line[index]))
			index++;
		prev_i = index;
		index += is_valid_input(&line[index]);
		if (prev_i != index)
			curr_line_width++;
		else
			return (0);
		while (ft_isspace(line[index]))
			index++;
	}
	return (curr_line_width);
}

void	parse_map(t_fdf_cont *cont, int fd)
{
	char	*curr_line;
	int		curr_line_width;

	cont->map_h = 0;
	cont->map_w = 0;
	cont->map_is_colored = false;
	curr_line = get_next_line(fd);
	while (curr_line)
	{
		curr_line_width = parse_map_line(curr_line);
		if (curr_line_width == 0)
			exit_on_err("Map error: one of the inputs is not an int \n");
		else if (cont->map_w == 0)
			cont->map_w = curr_line_width;
		else if (cont->map_w != curr_line_width)
			exit_on_err("Map error: map is not rectangular \n");
		cont->map_h += 1;
		free(curr_line);
		curr_line = get_next_line(fd);
	}
	close (fd);
	return ;
}
