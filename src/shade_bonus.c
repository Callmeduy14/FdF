#include "../include/fdf.h"

#include <math.h>

/* normal flat dari sel (x,y) dengan dua tepi +X dan +Y */
static void	norm_flat(int x, int y, t_app *a, float *n)
{
	float	ax, ay, az;
	float	bx, by, bz;
	float	nx, ny, nz;
	float	len;

	ax = 1.0f;
	ay = 0.0f;
	az = a->map.z[y][x + 1] - a->map.z[y][x];
	bx = 0.0f;
	by = 1.0f;
	bz = a->map.z[y + 1][x] - a->map.z[y][x];
	nx = ay * bz - az * by;
	ny = az * bx - ax * bz;
	nz = ax * by - ay * bx;
	len = sqrtf(nx * nx + ny * ny + nz * nz);
	if (len == 0.0f)
		len = 1.0f;
	n[0] = nx / len;
	n[1] = ny / len;
	n[2] = nz / len;
}

/* lerp RGB -> RGBA (alpha = 0xFF) */
static uint32_t	lerp_rgba(int rgb_a, int rgb_b, float t)
{
	int	ar = (rgb_a >> 16) & 255;
	int	ag = (rgb_a >> 8) & 255;
	int	ab = rgb_a & 255;
	int	br = (rgb_b >> 16) & 255;
	int	bg = (rgb_b >> 8) & 255;
	int	bb = rgb_b & 255;

	int r = (int)(ar + (br - ar) * t);
	int g = (int)(ag + (bg - ag) * t);
	int b = (int)(ab + (bb - ab) * t);

	/* RGBA: R<<24 | G<<16 | B<<8 | A */
	return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | 0xFF;
}

/* shading sederhana berbasis dot(N,L) */
uint32_t	shade_line(int x0, int y0, int x1, int y1, t_app *a)
{
	float		n[3];
	const float lx = -0.5f;
	const float ly = -0.6f;
	const float lz =  0.6f;
	float		dot;
	float		t;

	(void)x1;
	(void)y1;
	if (x0 + 1 >= a->map.w || y0 + 1 >= a->map.h)
		return 0xAAAAAAFF; /* default */
	norm_flat(x0, y0, a, n);
	dot = n[0] * lx + n[1] * ly + n[2] * lz;
	if (dot < 0.0f)
		dot = 0.0f;
	if (dot > 1.0f)
		dot = 1.0f;
	t = dot;
	return lerp_rgba(0x334455, 0xFFFFFF, t);
}
