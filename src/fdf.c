#include "fdf.h"
#include <sys/time.h>

void	do_mlx_loop(void *mlx_ptr)
{
	mlx_loop(mlx_ptr);
}

int	main(int argc, char *argv[])
{
	t_fdf_cont	*cont;

	if (argc != 2)
		exit_on_err("Error: FdF only accepts one input\n");
	cont = malloc(sizeof(t_fdf_cont));
	if (!cont)
		exit (1);
	fdf_parse(cont, argv[1]);
	fdf_init(cont, argv[1]);
	center_map(cont);
	display_map(cont);

	set_hooks(cont);
	do_mlx_loop(cont->mlx_ptr);

	fdf_cleanup(cont);
	return (0);
}
