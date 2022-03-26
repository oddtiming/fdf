#include "fdf.h"
#include <sys/time.h>

void	do_mlx_loop(void *mlx_ptr)
{
	mlx_loop(mlx_ptr);
}

void	test_linear_interpolation(t_fdf_cont *cont)
{
	double	start;
	double	end;
	double	curr;

	(void) cont;
	start = 0;
	end = 10;
	curr = 3;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));

	start = 10;
	end = -100;
	curr = 3;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));

	start = -50;
	end = 50;
	curr = 20;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));

	start = 1;
	end = 10;
	curr = 3;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));

	start = 10;
	end = 1;
	curr = 3;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));

	start = -1;
	end = -10;
	curr = -3;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));

	start = -10;
	end = -1;
	curr = -3;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));

	start = 10;
	end = 0;
	curr = 3;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));

	start = 10;
	end = 0;
	curr = 10;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));

	start = 10;
	end = 0;
	curr = 0;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));

	start = 10;
	end = 0;
	curr = 50;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));

	start = 0;
	end = 10;
	curr = 50;
	printf("start = %f \n", start);
	printf("end = %f \n", end);
	printf("curr = %f \n", curr);
	printf("linear_interpolation(start, end, curr) = %f \n", linear_interpolation(start, end, curr));
}

int	main(int argc, char *argv[])
{
	t_fdf_cont	*cont;

	cont = malloc(sizeof(t_fdf_cont));
	if (!cont)
		exit (1);
	if (argc != 2)
		exit_on_err("Error: FdF only accepts one input \n");
	fdf_parse(cont, argv[1]);
	fdf_init(cont, argv[1]);
	// print_map_info(cont, 0);
	center_map(cont);
	display_map(cont);
	test_linear_interpolation(cont);
	
	set_hooks(cont);
	do_mlx_loop(cont->mlx_ptr);

	fdf_cleanup(cont);
	return (0);
}
