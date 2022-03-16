#ifndef FDF_H
#define FDF_H

/**
 * @brief 
 * Libraries:
 */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "../libft/libft.h"


# ifndef DEBUG
#  define DEBUG 0
# endif

# define WIN_W 1280
# define WIN_H 1024


//TYPEDEFS
// Enums
enum e_colors
{
	FDF_BLACK	= 0x000000,
	FDF_CYAN	= 0x00FFFF,
	FDF_PINK	= 0xFF00FF,
	FDF_WHITE	= 0xFFFFFF,
	FDF_YELLOW	= 0xFFFF00
};

enum e_mlx_events
{
	DESTROY_NOTIFY = 17
};

// Structs
typedef struct s_2d_point
{
	int	x;
	int	y;
}	t_2d_point;

typedef struct	s_img
{
	void	*img_ptr;
	char	*data_addr;
	int		bpp;
	int		line_len;
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
//	init.c
int	init_fdf(t_fdf_cont *cont, char *map_name);

// Hooks
//	hooks.c
void	set_hooks(t_fdf_cont *cont);	
int		handle_expose_hook(t_fdf_cont *cont);
int		handle_key_hook(int keysym, t_fdf_cont *cont);
int		handle_mouse_hook(int button, int x, int y, t_fdf_cont *cont);
int		handle_default_hook(t_fdf_cont *cont);

// Image manipulation
//	draw_img.c
void	fill_pixel(t_img *img, int x, int y, int color);
void	fill_square_img_row(t_img *img, int size, int y, int color);

//	display.c
int		display_default(t_fdf_cont *cont);
int		display_img(t_fdf_cont *cont, t_img *img);
int		display_square(t_fdf_cont *cont);

//	draw.c
void	draw_square(t_img *img, int size);
void	put_square(t_fdf_cont *cont, t_img *img, int size);

// Cleanup
//	cleanup.c
int		fdf_clean_exit(t_fdf_cont *cont);
void	fdf_cleanup(t_fdf_cont *cont);

#endif