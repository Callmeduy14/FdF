/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_palette.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 03:20:34 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/22 16:19:48 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	lerp8(int a, int b, float t)
{
	float	tt;
	int		out;

	tt = t;
	if (tt < 0.0f)
		tt = 0.0f;
	if (tt > 1.0f)
		tt = 1.0f;
	tt = sqrtf(tt);
	out = (int)(a + (b - a) * tt);
	return (out);
}

static uint32_t	pack_rgba(int r, int g, int b)
{
	uint32_t	c;

	c = ((uint32_t)r << 24)
		| ((uint32_t)g << 16)
		| ((uint32_t)b << 8)
		| 0xFF;
	return (c);
}

static uint32_t	lerp_rgba_u24(uint32_t ca, uint32_t cb, float t)
{
	int	r;
	int	g;
	int	b;

	r = lerp8((int)((ca >> 16) & 255), (int)((cb >> 16) & 255), t);
	g = lerp8((int)((ca >> 8) & 255), (int)((cb >> 8) & 255), t);
	b = lerp8((int)(ca & 255), (int)(cb & 255), t);
	return (pack_rgba(r, g, b));
}

uint32_t	height_color(float z, const t_map *m)
{
	float	span;
	float	t;

	span = m->max_z - m->min_z;
	if (span <= 0.0f)
		span = 1.0f;
	t = (z - m->min_z) / span;
	if (t < 0.25f)
		return (lerp_rgba_u24(0x143C5A, 0x287882, t / 0.25f));
	if (t < 0.50f)
		return (lerp_rgba_u24(0x287882, 0x78AA5A, (t - 0.25f) / 0.25f));
	if (t < 0.75f)
		return (lerp_rgba_u24(0x78AA5A, 0xC8A05A, (t - 0.50f) / 0.25f));
	return (lerp_rgba_u24(0xC8A05A, 0xF5F0E6, (t - 0.75f) / 0.25f));
}
