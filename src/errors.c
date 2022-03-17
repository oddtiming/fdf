#include "fdf.h"

void	exit_on_err(char *err_message)
{
	write(STDERR_FILENO, err_message, ft_strlen(err_message));
	exit (EXIT_FAILURE);
}
