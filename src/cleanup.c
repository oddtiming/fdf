#include "fdf.h"

void	exit_on_err(char *err_message)
{
	write(STDERR_FILENO, err_message, ft_strlen(err_message));
	exit(EXIT_FAILURE);
}

int	fdf_clean_exit(t_fdf_cont *cont)
{
	fdf_cleanup(cont);
	exit(EXIT_SUCCESS);
}

void	fdf_cleanup(t_fdf_cont *cont)
{
	mlx_destroy_window(cont->mlx_ptr, cont->win_ptr);
	mlx_destroy_image(cont->mlx_ptr, cont->img->img_ptr);
	free(cont->win_name);
	free(cont->img);
	free(cont->map);
	free(cont);
	return ;
}
