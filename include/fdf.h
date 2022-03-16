#ifndef FDF_H
#define FDF_H

/**
 * @brief 
 * Libraries:
 */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "mlx.h"
# include "../libft/libft.h"


# ifndef DEBUG
#  define DEBUG 0
# endif


//TYPEDEFS
// Enums
enum e_colors
{
	FDF_WHITE = 255 << 24 | 255 << 16 | 255 << 8 | 255
};

// Structs
typedef struct s_mlx_ptrs
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct	s_img
{
	void	*img_ptr;
	char	*data_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_fdf_cont
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*display_img;
	int		height;
	int		width;
}	t_fdf_cont;




//FUNCTIONS
// Initialization
int	init_fdf(t_fdf_cont *cont, char *map_name);

// Hooks 
int	handle_expose_hook(t_fdf_cont *cont);
int	handle_key_hook(int keysym, t_fdf_cont *cont);
int	handle_mouse_hook(int button, int x, int y, t_fdf_cont *cont);
int	handle_default_hook(t_fdf_cont *cont);

//Basic draw functions
int	display_square(t_fdf_cont *mlx);


#endif