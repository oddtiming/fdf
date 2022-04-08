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

double	linear_interpolation(double start, double end, double curr)
{
	if (curr == start || end == start)
		return (0.0F);
	else if (curr == end)
		return (1.0F);
	return ((curr - start) / (end - start));
}
