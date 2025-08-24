/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_height.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:56:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/18 01:57:00 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clamp_zscale(t_app *a)
{
	if (a->cam.zscale < 0.05f)
		a->cam.zscale = 0.05f;
	if (a->cam.zscale > 10.0f)
		a->cam.zscale = 10.0f;
}

static void	add_height_offset(t_map *m, float delta)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			m->z[y][x] = m->z[y][x] + delta;
			x++;
		}
		y++;
	}
	m->min_z = m->min_z + delta;
	m->max_z = m->max_z + delta;
}

void	handle_height_keys(mlx_key_data_t k, t_app *a)
{
	if (k.key == MLX_KEY_U)
	{
		a->cam.zscale = a->cam.zscale * 1.10f;
		clamp_zscale(a);
	}
	else if (k.key == MLX_KEY_O)
	{
		a->cam.zscale = a->cam.zscale * 0.90f;
		clamp_zscale(a);
	}
	else if (k.key == MLX_KEY_M)
		add_height_offset(&a->map, 1.0f);
	else if (k.key == MLX_KEY_N)
		add_height_offset(&a->map, -1.0f);
}
