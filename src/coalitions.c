#include "fdf.h"

#define NB_INTERVALS 5

unsigned long const		g_intervals[NB_INTERVALS] = {
	1700,
	600,
	250,
	150,
	100};

static uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	flash_coalition_color(t_fdf *fdf)
{
	static uint64_t	start_time;
	uint64_t		time;
	int				colors[NB_COALITIONS] = { ARMADA, LEGION, TORRENT };
	static int		color_id;
	static int		interval_id = 0;
	static int		nb_loops;

	if (!start_time)
	{
		start_time = get_time();
		color_id = random() % NB_COALITIONS;
		fdf->coalition_color = colors[color_id];
	}
	fdf->force_colors = true;
	if (interval_id == NB_INTERVALS)
	{
		fdf->coalition_color = fdf->final_coa_color;
		printf("fdf->coalition_color = %#X\n", fdf->coalition_color);
		interval_id = 0;
		start_time = 0;
		fdf->toggle_coalitions = false;
		return ;
	}
	time = get_time();
	if (time - start_time >= g_intervals[interval_id])
	{
		if (++nb_loops == NB_COALITIONS * (interval_id + 1))
		{
			++interval_id;
			nb_loops = 0;
		}
		start_time = get_time();
		++color_id;
		color_id %= NB_COALITIONS;
		fdf->coalition_color = colors[color_id];
	}
}
