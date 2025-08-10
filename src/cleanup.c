#include "../include/fdf.h"

void	free_map(t_map *m)
{
	int	i;

	if (!m || !m->z)
		return ;
	i = 0;
	while (i < m->h)
	{
		free(m->z[i]);
		i++;
	}
	free(m->z);
	m->z = 0;
}

/* Bersihkan seluruh resource aplikasi (versi MLX42) */
void	app_cleanup(t_app *a)
{
	if (!a)
		return ;
	if (a->img)
		mlx_delete_image(a->mlx, a->img);
	if (a->mlx)
		mlx_terminate(a->mlx);
	free_map(&a->map);
}

/* Error helper (aman untuk MLX42) */
void	panic(t_app *a, const char *msg, int err)
{
	if (msg)
		write(2, msg, (int)ft_strlen(msg));
	app_cleanup(a);
	if (err)
		exit(err);
}
