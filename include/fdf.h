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
# include "iterators.h"
# include "../libft/libft.h"


# ifndef DEBUG
#  define DEBUG 0
# endif


//TYPEDEFS
// Enums
typedef enum
{
	FDF_BLACK	= 0x000000,
	FDF_BLUE	= 0x0000FF,
	FDF_CYAN	= 0x00FFFF,
	FDF_GREY	= 0x222222,
	FDF_ORANGE	= 0xFF7700,
	FDF_PINK	= 0xFF00FF,
	FDF_RED		= 0xFF0000,
	FDF_WHITE	= 0xFFFFFF,
	FDF_YELLOW	= 0xFFFF00
} e_colors;

typedef enum
{
	DESTROY_NOTIFY = 17
} e_mlx_events;

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

typedef struct s_line
{
	t_point	p1;
	t_point	p2;
	double	*independent_var;
	double	*dependent_var;
	int	independent_max;
	int	independent_step;
	int	dependent_step;
	int	offset_increment;
	int	offset_decrement;
	int	offset;
	int	dx;
	int	dy;
}	t_line;


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


typedef struct s_fdf_cont
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
	bool	map_is_colored;
	bool	toggle_rot_x;
	bool	toggle_rot_y;
	bool	toggle_rot_z;
	bool	toggle_menu;
	bool	toggle_proj;
}	t_fdf_cont;


//FUNCTIONS
// Initialization

//  parse.c
void	fdf_parse(t_fdf_cont *cont, char *filepath);
void	parse_map(t_fdf_cont *cont, int fd);
int		parse_map_line(char *curr_line);

// assign.c
void	assign_limits(t_fdf_cont *cont);
void	assign_map(t_fdf_cont *cont, int fd);
void	assign_map_line(t_fdf_cont *cont, char *line, int y);
void	assign_colors(t_fdf_cont *cont);

//	init.c
void	fdf_init(t_fdf_cont *cont, char *filepath);

// Hooks
//	hooks.c
void	set_hooks(t_fdf_cont *cont);	
int		handle_expose_hook(t_fdf_cont *cont);
int		handle_key_hook(int keysym, t_fdf_cont *cont);
int		handle_keypress_hook(int keysym, t_fdf_cont *cont);
int		handle_mouse_hook(int button, int x, int y, t_fdf_cont *cont);
int		handle_default_hook(t_fdf_cont *cont);

// Image manipulation
//	draw_img.c
void	fill_pixel(t_img *img, int x, int y, int color);

//	display.c
int		display_default(t_fdf_cont *cont);
int		display_img(t_fdf_cont *cont, t_img *img);
int		display_square_rainbow(t_fdf_cont *cont);
void	test_display_lines(t_fdf_cont *cont);
void	test_display_lines_multicolor(t_fdf_cont *cont);
void	display_lines_until_x(t_fdf_cont *cont);

//  display_map.c
void	display_map(t_fdf_cont *cont);
void	center_map(t_fdf_cont *cont);
void	project_point(t_fdf_cont *cont, t_angles *angles, int x, int y);

//	display_menu.c
void	display_menu(t_fdf_cont *cont);

//	draw.c
void	draw_background(t_img *img, int color);
void	draw_line(t_fdf_cont *cont, t_point p1, t_point p2);
void	draw_square_rainbow(t_img *img, int size);
void	draw_line_rainbow(t_img *img, t_point p1, t_point p2);
void	draw_line_rainbow_offset(t_img *img, t_point p1, t_point p2, int offset);

// rotate.c
void	rotate_map(t_fdf_cont *cont);
void	rotate_z(t_fdf_cont *cont, double theta);
void	rotate_y(t_fdf_cont *cont, double theta);
void	rotate_x(t_fdf_cont *cont, double theta);

// 	color.c
void	change_color(int x, int y, int *color);
void	change_color_offset(int x, int y, int *color, int offset);
int		average_color(int color1, int color2, double percent);

// Utils
//	utils.c
void	*ft_safealloc(size_t size);
void	print_map(t_fdf_cont *cont);
void	print_map_info(t_fdf_cont *cont, int map_val);
double	fdf_strtodbl(char *str);
double	linear_interpolation(double start, double end, double curr);
bool	is_within_bounds(t_fdf_cont *cont, t_point const *const p);

// Cleanup
//	cleanup.c
int		fdf_clean_exit(t_fdf_cont *cont);
void	fdf_cleanup(t_fdf_cont *cont);
void	exit_on_err(char *err_message);


#endif