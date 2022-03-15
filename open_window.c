#include "./minilibx_macos/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_ptrs
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_ptrs;

int	close_window(int keysym, void *param)
{
	t_ptrs	*ptr;

	ptr = (t_ptrs *) param;
	if (keysym == 53)
	{
		mlx_destroy_window(ptr->mlx_ptr, ptr->win_ptr);
		exit(1);
		return (1);
	}
	return (0);
}

int	main(void)
{
	void	*mlx_ptr, *win_ptr;
	char	*title = "open_window_test";
	int		size_x;
	int		size_y;
	t_ptrs	ptrs_struct;

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
	ptrs_struct.mlx_ptr = mlx_ptr;
	ptrs_struct.win_ptr = win_ptr;

	mlx_hook();
	mlx_key_hook(win_ptr, close_window, &ptrs_struct);
	mlx_loop(mlx_ptr);
	sleep(1);
	mlx_clear_window(mlx_ptr, win_ptr);
	sleep(1);
	mlx_destroy_window(mlx_ptr, win_ptr);

	free(mlx_ptr);
	return (0);
}
