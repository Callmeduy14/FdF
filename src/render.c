/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:03:57 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/19 09:26:28 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	img_clear(t_app *a)
{
	int	total;
	int	i;

	total = a->img->width * a->img->height * 4;
	i = 0;
	while (i < total)
	{
		a->img->pixels[i] = 0;
		a->img->pixels[i + 1] = 0;
		a->img->pixels[i + 2] = 0;
		a->img->pixels[i + 3] = 255;
		i += 4;
	}
}

static void	draw_hud(t_app *a)
{
	if (a->hud)
		mlx_delete_image(a->mlx, a->hud);
	a->hud = mlx_put_string(a->mlx,
			" ESC Exit | +/- zoom | [ ] angle | "
			"U/O zscale | A anim | Z shade | "
			"C/F/G/IJKL | R reset",
			10, 10);
}

void	render_scene(t_app *a)
{
	int	y;

	img_clear(a);
	if (a->anim_on)
		apply_animation(a, a->time, 0.80f, 1.80f);
	y = a->map.h - 1;
	while (y >= 0)
	{
		draw_grid_row(a, y);
		y--;
	}
	render_pivot(a);
	draw_hud(a);
}
