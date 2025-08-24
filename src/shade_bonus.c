/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 03:00:32 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/23 12:11:29 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <math.h>

static void	norm_flat(int x, int y, t_app *a, float *n)
{
	float	dzx;
	float	dzy;
	float	nz;
	float	s;
	float	inv;

	dzx = a->map.z[y][x + 1] - a->map.z[y][x];
	dzy = a->map.z[y + 1][x] - a->map.z[y][x];
	nz = 1.0f;
	s = (dzx * dzx) + (dzy * dzy) + (nz * nz);
	if (s == 0.0f)
		s = 1.0f;
	inv = 1.0f / sqrtf(s);
	n[0] = (-dzx) * inv;
	n[1] = (-dzy) * inv;
	n[2] = nz * inv;
}

static uint32_t	lerp_rgba(int rgb_a, int rgb_b, float t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((rgb_a >> 16) & 255) + (((rgb_b >> 16) & 255)
				- ((rgb_a >> 16) & 255)) * t);
	g = (int)(((rgb_a >> 8) & 255) + (((rgb_b >> 8) & 255)
				- ((rgb_a >> 8) & 255)) * t);
	b = (int)((rgb_a & 255) + ((rgb_b & 255)
				- (rgb_a & 255)) * t);
	return (((uint32_t)r << 24)
		| ((uint32_t)g << 16)
		| ((uint32_t)b << 8)
		| 0xFF);
}

uint32_t	shade_line(t_pt2 p0, t_pt2 p1, t_app *a)
{
	float	n[3];
	float	lx;
	float	ly;
	float	lz;
	float	dot;

	(void)p1;
	lx = -0.5f;
	ly = -0.6f;
	lz = 0.6f;
	if (p0.x + 1 >= a->map.w || p0.y + 1 >= a->map.h)
		return (0xAAAAAAFF);
	norm_flat(p0.x, p0.y, a, n);
	dot = (n[0] * lx) + (n[1] * ly) + (n[2] * lz);
	if (dot < 0.0f)
		dot = 0.0f;
	if (dot > 1.0f)
		dot = 1.0f;
	return (lerp_rgba(0x334455, 0xFFFFFF, dot));
}
