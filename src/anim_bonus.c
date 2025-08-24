/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 03:05:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/22 16:14:26 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	anim_reset_clock(t_app *a, float t0)
{
	a->last_t = t0;
	a->anim_inited = 1;
}

static float	sample_mix(float t, int i, int j, const t_wave *w)
{
	float	dx;
	float	dy;
	float	r;
	float	p1;
	float	res;

	dx = (float)j - w->cx;
	dy = (float)i - w->cy;
	r = sqrtf(dx * dx + dy * dy);
	p1 = t * w->speed + w->kx * (float)j + w->ky * (float)i;
	res = 0.60f * sinf(p1);
	res = res + 0.30f * sinf(t * w->speed * 1.7f
			+ 0.5f * w->kx * (float)j - 0.5f * w->ky * (float)i);
	res = res + 0.10f * sinf(t * w->speed * 0.6f + 1.2f * r);
	return (w->ampl * res);
}

static void	apply_rows(t_map *m, float t, float last_t, const t_wave *w)
{
	int		y;
	int		x;
	float	nowv;
	float	lastv;

	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			nowv = sample_mix(t, y, x, w);
			lastv = sample_mix(last_t, y, x, w);
			m->z[y][x] = m->z[y][x] + (nowv - lastv);
			x = x + 1;
		}
		y = y + 1;
	}
}

void	apply_animation(t_app *a, float t, float ampl, float speed)
{
	t_wave	w;

	if (a->map.w <= 1 || a->map.h <= 1)
		return ;
	w.ampl = ampl;
	w.speed = speed;
	w.kx = (float)(2.0f * M_PI)*1.8f / (float)(a->map.w - 1);
	w.ky = (float)(2.0f * M_PI)*1.8f / (float)(a->map.h - 1);
	w.cx = ((float)(a->map.w - 1)) * 0.5f;
	w.cy = ((float)(a->map.h - 1)) * 0.5f;
	if (!a->anim_inited)
		anim_reset_clock(a, t);
	apply_rows(&a->map, t, a->last_t, &w);
	a->last_t = t;
}
