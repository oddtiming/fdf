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
	while (y < cont->map_height)
	{
		x = 0;
		while (x < cont->map_width)
		{
			printf(" %3.3f ", cont->map[x + (y * cont->map_width)].z);
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
	while (y < cont->map_height)
	{
		x = 0;
		while (x < cont->map_width)
		{
			if (map_val == 0)
			{
				if (x == 0 && y == 0)
					printf("\t==> X values \n");
				printf(" %3.3f ", cont->map[x + (y * cont->map_width)].x);
			}
			else if (map_val == 1)
			{
				if (x == 0 && y == 0)
					printf("\t==> Y values \n");
				printf(" %3.3f ", cont->map[x + (y * cont->map_width)].y);
			}
			else
			{
				if (x == 0 && y == 0)
					printf("\t==> Z values \n");
				printf(" %3.3f ", cont->map[x + (y * cont->map_width)].z);
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
	return ;
}
