/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:30:50 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/22 21:38:07 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_cam(t_cam *c)
{
	c->angle = 0.785f;
	c->zscale = 0.3f;
	c->rot_x = 0.0f;
	c->rot_y = 0.0f;
	c->rot_z = 0.0f;
	c->pan_x = (float)(WIN_W / 2);
	c->pan_y = (float)(WIN_H / 3);
	c->zoom = 20.0f;
	c->pivot_x = 0.0f;
	c->pivot_y = 0.0f;
	c->pivot_z = 0.0f;
}

static int	load_map(const char *path, t_map *m)
{
	if (parse_fdf(path, m))
	{
		write(2, "parse error\n", 12);
		return (1);
	}
	return (0);
}

int	init_window_and_image(t_app *a)
{
	a->mlx = mlx_init(WIN_W, WIN_H, "fdf", 0);
	if (!a->mlx)
	{
		write(2, "mlx_init failed\n", 16);
		return (1);
	}
	a->img = mlx_new_image(a->mlx, WIN_W, WIN_H);
	if (!a->img || mlx_image_to_window(a->mlx, a->img, 0, 0) < 0)
	{
		write(2, "image init failed\n", 18);
		return (1);
	}
	return (0);
}

static void	init_state(t_app *a)
{
	a->anim_on = 0;
	a->shade_on = 0;
	a->time = 0.0f;
	a->hud = 0;
	a->dragging = 0;
	a->needs_redraw = 1;
}

int	init_app(t_app *a, const char *path)
{
	init_state(a);
	if (load_map(path, &a->map))
		return (1);
	init_cam(&a->cam);
	set_pivot_center(a);
	fit_to_view(a);
	if (init_window_and_image(a))
		return (1);
	events_init(a);
	render_scene(a);
	return (0);
}
