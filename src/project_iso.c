/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_iso.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:58:28 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/22 19:50:44 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_point(t_pt3 *p, float rx, float ry, float rz)
{
	float	x;
	float	y;
	float	z;

	y = p->y * cosf(rx) - p->z * sinf(rx);
	z = p->y * sinf(rx) + p->z * cosf(rx);
	p->y = y;
	p->z = z;
	x = p->x * cosf(ry) + p->z * sinf(ry);
	z = -p->x * sinf(ry) + p->z * cosf(ry);
	p->x = x;
	p->z = z;
	x = p->x * cosf(rz) - p->y * sinf(rz);
	y = p->x * sinf(rz) + p->y * cosf(rz);
	p->x = x;
	p->y = y;
}

t_pt2	project_iso(t_pt3 p, t_cam c)
{
	t_pt2	out;
	float	x2d;
	float	y2d;

	p.x -= c.pivot_x;
	p.y -= c.pivot_y;
	p.z -= c.pivot_z;
	rotate_point(&p, c.rot_x, c.rot_y, c.rot_z);
	p.x += c.pivot_x;
	p.y += c.pivot_y;
	p.z += c.pivot_z;
	x2d = (p.x - p.y) * cosf(c.angle);
	y2d = (p.x + p.y) * sinf(c.angle) - p.z * c.zscale;
	out.x = (int)(x2d * c.zoom + c.pan_x);
	out.y = (int)(y2d * c.zoom + c.pan_y);
	out.color = 0xFFFFFFFF;
	return (out);
}
