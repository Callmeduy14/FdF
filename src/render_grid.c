/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 03:23:27 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/18 03:23:28 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint32_t	col_h(t_app *a, int y, int x)
{
	t_pt2		s0;
	t_pt2		s1;
	float		avg;

	if (a->shade_on)
	{
		s0.x = x;
		s0.y = y;
		s1.x = x + 1;
		s1.y = y;
		return (shade_line(s0, s1, a));
	}
	avg = (a->map.z[y][x] + a->map.z[y][x + 1]) * 0.5f;
	return (height_color(avg, &a->map));
}

static uint32_t	col_v(t_app *a, int y, int x)
{
	t_pt2		s0;
	t_pt2		s1;
	float		avg;

	if (a->shade_on)
	{
		s0.x = x;
		s0.y = y;
		s1.x = x;
		s1.y = y + 1;
		return (shade_line(s0, s1, a));
	}
	avg = (a->map.z[y][x] + a->map.z[y + 1][x]) * 0.5f;
	return (height_color(avg, &a->map));
}

static void	draw_h_segment(t_app *a, int y, int x)
{
	uint32_t	col;
	t_pt3		p0;
	t_pt3		p1;

	if (x + 1 >= a->map.w)
		return ;
	col = col_h(a, y, x);
	p0.x = x;
	p0.y = y;
	p0.z = a->map.z[y][x];
	p1.x = x + 1;
	p1.y = y;
	p1.z = a->map.z[y][x + 1];
	draw_line(a, project_iso(p0, a->cam), project_iso(p1, a->cam), col);
}

static void	draw_v_segment(t_app *a, int y, int x)
{
	uint32_t	col;
	t_pt3		p0;
	t_pt3		p1;

	if (y + 1 >= a->map.h)
		return ;
	col = col_v(a, y, x);
	p0.x = x;
	p0.y = y;
	p0.z = a->map.z[y][x];
	p1.x = x;
	p1.y = y + 1;
	p1.z = a->map.z[y + 1][x];
	draw_line(a, project_iso(p0, a->cam), project_iso(p1, a->cam), col);
}

void	draw_grid_row(t_app *a, int y)
{
	int	x;

	x = 0;
	while (x < a->map.w)
	{
		draw_h_segment(a, y, x);
		draw_v_segment(a, y, x);
		x++;
	}
}
