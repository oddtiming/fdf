#include "./minilibx_macos/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	void	*mlx_ptr, *win_ptr;
	char	*title = "open_window_test";
	int		size_x;
	int		size_y;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (0);
	size_x = 800;
	size_y = 800;
	win_ptr = mlx_new_window(mlx_ptr, size_x, size_y, title);
	if (!win_ptr)
	{
		free (mlx_ptr);
		mlx_ptr = NULL;
		return (0);
	}
	mlx_loop(mlx_ptr);
	sleep(1);
	mlx_clear_window(mlx_ptr, win_ptr);
	sleep(1);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);

	free(mlx_ptr);
	return (0);
}
