#include "../include/fdf.h"

static float	wave_z(float t, int i, int j, float ampl, float freq)
{
	float	val;

	val = sinf(t + (i + j) * freq) * ampl;
	return (val);
}

void	apply_animation(t_map *m, float t, float ampl, float freq)
{
	int		i;
	int		j;

	i = 0;
	while (i < m->h)
	{
		j = 0;
		while (j < m->w)
		{
			m->z[i][j] = m->z[i][j] + wave_z(t, i, j, ampl, freq);
			j++;
		}
		i++;
	}
}
