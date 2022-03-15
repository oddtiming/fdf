#ifndef FDF_H
#define FDF_H

/**
 * @brief 
 * Libraries:
 */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"


# ifndef DEBUG
#  define DEBUG 0
# endif


//TYPEDEFS
// Enums
enum e_colors
{
	FDF_WHITE = 0xFFFFFF
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
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

//FUNCTIONS
// Hooks 
int	handle_expose_hook(void *param);
int	handle_key_hook(int keysym, void *param);
int	handle_mouse_hook(int button, int x, int y, void *param);

//Basic draw functions
int	draw_square(t_mlx *mlx);


#endif