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
	size_x = 100;
	size_y = 100;
	win_ptr = mlx_new_window(mlx_ptr, size_x, size_y, title);
	mlx_loop(mlx_ptr);
	sleep(3);
	mlx_clear_window(mlx_ptr, win_ptr);
	sleep(3);
	mlx_destroy_window(mlx_ptr, win_ptr);

	free(mlx_ptr);
	return (0);
}
