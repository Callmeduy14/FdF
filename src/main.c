/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 03:23:50 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/24 14:55:21 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	update_time_and_flag(t_app *a, double last)
{
	double	now;
	double	dt;

	now = mlx_get_time();
	if (last == 0.0)
		dt = 1.0 / 60.0;
	else
		dt = now - last;
	if (a->anim_on)
	{
		a->time += (float)dt;
		a->needs_redraw = 1;
	}
	return (now);
}

void	render_loop(void *param)
{
	static double	last = 0.0;
	t_app			*a;

	a = (t_app *)param;
	last = update_time_and_flag(a, last);
	if (!a->needs_redraw)
		return ;
	a->needs_redraw = 0;
	render_scene(a);
}

int	main(int ac, char **av)
{
	t_app	a;

	if (ac != 2)
	{
		write(2, "usage: ./fdf map.fdf\n", 22);
		return (1);
	}
	if (init_app(&a, av[1]))
		return (app_cleanup(&a),1);
	mlx_loop_hook(a.mlx, render_loop, &a);
	mlx_loop(a.mlx);
	app_cleanup(&a);
	return (0);
}
