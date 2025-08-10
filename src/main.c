#include "fdf.h"
#include <unistd.h>

/* kamera awal */
static void	init_cam(t_cam *c)
{
	c->angle = M_PI / 6.0f;
	c->scale = 20.0f;
	c->zscale = 1.0f;
	c->offx = WIN_W / 2;
	c->offy = WIN_H / 3;
}

/* loop hook: dipanggil tiap frame oleh MLX42 */
static void	render_loop(void *param)
{
	t_app	*a;

	a = (t_app *)param;
	if (a->anim_on)
		a->time += 0.016f;
	if (a->anim_on || a->shade_on)
		render_scene(a);
}

/* inisialisasi app + grafik */
static int	init_app(t_app *a, const char *path)
{
	a->anim_on = 0;
	a->shade_on = 0;
	a->time = 0.0f;
	if (parse_fdf(path, &a->map))
		return (write(2, "parse error\n", 12), 1);
	init_cam(&a->cam);
	a->mlx = mlx_init(WIN_W, WIN_H, "fdf", 0);
	if (!a->mlx)
		return (write(2, "mlx_init failed\n", 16), 1);
	a->img = mlx_new_image(a->mlx, WIN_W, WIN_H);
	if (!a->img || mlx_image_to_window(a->mlx, a->img, 0, 0) < 0)
		return (write(2, "image init failed\n", 18), 1);
	key_hook_init(a);
	render_scene(a);
	return (0);
}

int	main(int ac, char **av)
{
	t_app	a;

	if (ac != 2)
		return (write(2, "usage: ./fdf map.fdf\n", 22), 1);
	if (init_app(&a, av[1]))
		return (1);
	mlx_loop_hook(a.mlx, render_loop, &a);
	mlx_loop(a.mlx);
	app_cleanup(&a);
	return (0);
}
