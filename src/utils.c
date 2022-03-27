#include "fdf.h"

void	*ft_safealloc(size_t size)
{
	void	*mem_space;

	mem_space = malloc(size);
	if (!mem_space)
	{
		write(STDERR_FILENO, "Malloc Error\n", 13);
		exit (EXIT_FAILURE);
	}
	return (mem_space);
}

void	print_map(t_fdf_cont *cont)
{
	int			x;
	int			y;

	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			printf(" %3.3f ", cont->map[x + (y * cont->map_w)].z);
			x++;
		}
		printf("\n");
		y++;
	}
	return ;
}

void	print_map_info(t_fdf_cont *cont, int map_val)
{
	int			x;
	int			y;


	y = 0;
	while (y < cont->map_h)
	{
		x = 0;
		while (x < cont->map_w)
		{
			if (map_val == 0)
			{
				if (x == 0 && y == 0)
					printf("\t==> X values \n");
				printf(" %3.3f ", cont->map[x + (y * cont->map_w)].x);
			}
			else if (map_val == 1)
			{
				if (x == 0 && y == 0)
					printf("\t==> Y values \n");
				printf(" %3.3f ", cont->map[x + (y * cont->map_w)].y);
			}
			else if (map_val == 2)
			{
				if (x == 0 && y == 0)
					printf("\t==> Z values \n");
				printf(" %3.3f ", cont->map[x + (y * cont->map_w)].z);
			}
			else
			{
				if (x == 0 && y == 0)
					printf("\t==> Colors \n");
				printf(" %8X ", cont->map[x + (y * cont->map_w)].color);
			}
			x++;
		}
		printf("\n");
		y++;
	}
	if (map_val < 3)
	{
		printf("\n\n");
		print_map_info(cont, map_val + 1);
	}
	else
	{
		printf("cont->map_w = %d \n", cont->map_w);
		printf("cont->map_h = %d \n", cont->map_h);
		printf("cont->win_w = %d \n", cont->win_w);
		printf("cont->win_h = %d \n", cont->win_h);
	}
	return ;
}

double	fdf_strtodbl(char *str)
{
	int				integer;
	unsigned int	decimal;
	int				index;

	index = 0;
	integer = 0;
	decimal = 0;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '-' || ft_isdigit(str[index]))
	{
		integer = ft_atoi(&str[index]);
		index += ft_log_calc(integer, 10);
		if (integer < 0)
			index++;
	}
	if (str[index] == ',')
	{
		index++;
		decimal = ft_atox(&str[index]);
	}
	while (is_set(str[index], "0123456789ABCDEFabcdefx"))
		index++;
	return (integer + (decimal / __exp10(ft_log_calc(decimal, 10))));
}

double	linear_interpolation(double start, double end, double curr)
{
	if (curr == start || end == start)
		return (0.0F);
	else if (curr == end)
		return (1.0F);
	return ((curr - start) / (end - start));
}

bool	is_within_bounds(t_fdf_cont *cont, t_point const *const p)
{
	if (p->x < 0 || p->y < 0 || p->x > cont->win_w || p->y > cont->win_h)
		return (false);
	return (true);
}
