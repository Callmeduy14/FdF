#include "../include/fdf.h"

t_pt2	project_iso(t_pt3 p, t_cam c)
{
	t_pt2	out;
	float	x;
	float	y;

	x = (p.x - p.y) * cosf(c.angle);
	y = (p.x + p.y) * sinf(c.angle) - p.z;
	out.x = (int)(x * c.scale) + c.offx;
	out.y = (int)(y * c.scale) + c.offy;
	out.color = 0xFFFFFF;
	return (out);
}
