#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_fdf_cont	*cont;

	if (argc != 2)
		exit_on_err("Error: FdF only accepts one input\n");
	cont = ft_safealloc(sizeof(t_fdf_cont));
	fdf_parse(cont, argv[1]);
	fdf_init(cont, argv[1]);
	center_map(cont);
	display_map(cont);
	set_hooks(cont);
	mlx_loop(cont->mlx_ptr);
	return (0);
}
