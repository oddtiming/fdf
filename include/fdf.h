#ifndef FDF_H
# define FDF_H

/**
 * @brief 
 * Libraries:
 */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>	// clock()
# include <sys/time.h>	// gettimeofday() 
# include "mlx.h"
# include "iterators.h"
# include "../libft/libft.h"

# ifndef DEBUG
#  define DEBUG 0
# endif



# define WIN_W 1200
# define WIN_H	(WIN_W * 9 / 16)
# define NB_COALITIONS 3

// Enums
typedef enum e_colors
{
	BLACK	= 0x000000,
	BLUE	= 0x0000FF,
	CYAN	= 0x00FFFF,
	GREY	= 0x222222,
	GREEN	= 0x00FF00,
	ORANGE	= 0xFF7700,
	PINK	= 0xFF00FF,
	RED		= 0xFF0000,
	WHITE	= 0xFFFFFF,
	YELLOW	= 0xFFFF00
}	t_colors;

typedef enum e_coa_colors
{
	ARMADA	= 0x80FC6C,
	LEGION	= 0xF04C44,
	TORRENT	= 0x68A4DC
}	t_coa_colors;

// Structs
typedef struct s_point
{
	double			x;
	double			y;
	double			z;
	unsigned int	color;
}	t_point;

typedef struct s_angles
{
	double	sin_x;
	double	sin_y;
	double	sin_z;
	double	cos_x;
	double	cos_y;
	double	cos_z;
}	t_angles;

typedef struct s_bresenham
{
	t_point	p1;
	t_point	p2;
	double	*indep_var;
	double	*dep_var;
	int		indep_max;
	int		indep_step;
	int		dep_step;
	int		offset_increment;
	int		offset_decrement;
	int		offset;
	int		dx;
	int		dy;
	bool	is_reverse;
}	t_bresenham;

typedef struct s_img
{
	void	*img_ptr;
	char	*data_addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*win_name;
	t_img	*img;
	t_point	*map;
	double	z_divisor;
	double	theta_x;
	double	theta_y;
	double	theta_z;
	int		map_h;
	int		map_w;
	int		win_h;
	int		win_w;
	int		max_alt;
	int		min_alt;
	int		x_offset;
	int		y_offset;
	int		z_offset;
	int		square_width;
	int		coalition_color;
	int		final_coa_color;
	bool	map_is_colored;
	bool	toggle_rot_x;
	bool	toggle_rot_y;
	bool	toggle_rot_z;
	bool	toggle_menu;
	bool	toggle_proj;
	bool	toggle_coalitions;
	bool	force_colors;
	bool	toggle_mouse_rot;
}	t_fdf;

//FUNCTIONS
//  coalitions.c
void	flash_coalition_color(t_fdf *fdf);

// Initialization
//  parse.c
void	fdf_parse(t_fdf *cont, char *filepath);
void	parse_map(t_fdf *cont, int fd);

//	assign.c
void	assign_limits(t_fdf *cont);
void	assign_map(t_fdf *cont, int fd);

//	assign_colors.c
void	assign_colors(t_fdf *cont);

//	init.c
void	fdf_init(t_fdf *cont, char *filepath);
void	reset_proportions(t_fdf *cont);

// Hooks
//	hooks.c
void	set_hooks(t_fdf *cont);	

// Object Manipulation
//	matrix.c
void	center_map(t_fdf *cont);
void	apply_matrix(t_fdf *cont, t_angles *angles, t_point *p);
void	apply_scale(t_fdf *cont, t_point *p);
void	apply_rotation(t_angles *angles, t_point *p);
void	apply_translation(t_fdf *cont, t_point *p);

// Image Manipulation
//	display.c
int		display_default(t_fdf *cont);
int		display_img(t_fdf *cont, void *img_ptr);

//  display_map.c
void	display_map(t_fdf *cont);
void	project_point(t_fdf *cont, t_angles *angles, int x, int y);

//	display_menu.c
void	display_menu(t_fdf *cont);

//	bresenham.c
void	draw_line(t_fdf *cont, t_point p1, t_point p2);

//	line_clipping.c
int		line_clipping(t_fdf *cont, t_point *p1, t_point *p2);

// 	color.c
void	change_color(int x, int y, int *color);
void	change_color_offset(int x, int y, int *color, int offset);
int		average_color(int color1, int color2, double percent);

//	project.c
void	project_perspective(t_fdf *cont, t_point *p);
void	cycle_orthographic_perspectives(t_fdf *cont);

// Utils
//	utils.c
void	*ft_safealloc(size_t size);
double	linear_interpolation(double start, double end, double curr);
void	draw_background(t_img *img, int color);
void	fill_pixel(t_img *img, int x, int y, int color);

// Cleanup
//	cleanup.c
int		fdf_clean_exit(t_fdf *cont);
void	fdf_cleanup(t_fdf *cont);
void	exit_on_err(char *err_message);

#endif