/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pivot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 03:07:45 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/18 03:07:46 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	pivot_nearest_index(float v, int max)
{
	int		i;
	float	frac;

	if (v < 0.0f)
		v = 0.0f;
	if (v > (float)max)
		v = (float)max;
	i = (int)v;
	frac = v - (float)i;
	if (frac >= 0.5f && i < max)
		i = i + 1;
	if (i < 0)
		i = 0;
	if (i > max)
		i = max;
	return (i);
}

static float	pivot_height(const t_map *m, float fx, float fy)
{
	int	x;
	int	y;

	if (m->w <= 0 || m->h <= 0)
		return (0.0f);
	x = pivot_nearest_index(fx, m->w - 1);
	y = pivot_nearest_index(fy, m->h - 1);
	return (m->z[y][x]);
}

static void	draw_cross(t_app *a, t_pt2 c, int s, uint32_t col)
{
	t_pt2	p0;
	t_pt2	p1;

	p0 = c;
	p1 = c;
	p0.x = c.x - s;
	p1.x = c.x + s;
	draw_line(a, p0, p1, col);
	p0 = c;
	p1 = c;
	p0.y = c.y - s;
	p1.y = c.y + s;
	draw_line(a, p0, p1, col);
}

void	render_pivot(t_app *a)
{
	t_pt3		pw;
	t_pt2		pc;
	uint32_t	col;

	pw.x = (int)a->cam.pivot_x;
	pw.y = (int)a->cam.pivot_y;
	pw.z = pivot_height(&a->map, a->cam.pivot_x, a->cam.pivot_y);
	pc = project_iso(pw, a->cam);
	col = (((uint32_t)255 << 24) | ((uint32_t)220 << 16)
			| ((uint32_t)50 << 8) | 0xFF);
	draw_cross(a, pc, 5, col);
}
