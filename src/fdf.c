#include "fdf.h"

void	do_mlx_loop(void *mlx_ptr)
{
	mlx_loop(mlx_ptr);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*title = "open_window_test";
	int		size_x;
	int		size_y;
	t_mlx	mlx;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (0);
	size_x = 800;
	size_y = 800;
	win_ptr = mlx_new_window(mlx_ptr, size_x, size_y, title);
	if (!win_ptr)
	{
		free (mlx_ptr);
		return (0);
	}
	mlx.mlx_ptr = mlx_ptr;
	mlx.win_ptr = win_ptr;

	mlx_expose_hook(win_ptr, handle_expose_hook, &mlx);
	mlx_key_hook(win_ptr, handle_key_hook, &mlx);
	mlx_mouse_hook(win_ptr, handle_mouse_hook, &mlx);

	mlx_loop_hook(mlx_ptr, draw_square, &mlx);

	do_mlx_loop(mlx_ptr);


	// free(mlx_ptr);
	return (0);
}
