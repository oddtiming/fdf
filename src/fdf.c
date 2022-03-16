#include "fdf.h"

void	do_mlx_loop(void *mlx_ptr)
{
	mlx_loop(mlx_ptr);
}

int	main(void)
{
	t_fdf_cont	cont;
	char		*title = "open_window_test";

	cont.height = 800;
	cont.width = 800;
	if (init_fdf(&cont, title))
		return (0);

	mlx_expose_hook(cont.win_ptr, handle_expose_hook, &cont);
	mlx_key_hook(cont.win_ptr, handle_key_hook, &cont);
	mlx_mouse_hook(cont.win_ptr, handle_mouse_hook, &cont);

	mlx_loop_hook(cont.mlx_ptr, handle_default_hook, &cont);

	do_mlx_loop(cont.mlx_ptr);


	// free(mlx_ptr);
	return (0);
}


//Tutorial : https://www.youtube.com/c/BrendanGalea/videos