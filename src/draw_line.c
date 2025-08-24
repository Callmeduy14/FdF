/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:40:11 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/18 01:40:12 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	int_abs(int v)
{
	if (v < 0)
		return (-v);
	return (v);
}

static void	put_px(t_app *a, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	mlx_put_pixel(a->img, x, y, color);
}

static void	init_dirs(int *sx, int *sy, t_pt2 p, t_pt2 q)
{
	if (p.x < q.x)
		*sx = 1;
	else
		*sx = -1;
	if (p.y < q.y)
		*sy = 1;
	else
		*sy = -1;
}

static void	step_line(int *x, int *y, int *err, int dx_dy_sx_sy[4])
{
	int	e2;

	e2 = *err + *err;
	if (e2 > -dx_dy_sx_sy[1])
	{
		*err -= dx_dy_sx_sy[1];
		*x += dx_dy_sx_sy[2];
	}
	if (e2 < dx_dy_sx_sy[0])
	{
		*err += dx_dy_sx_sy[0];
		*y += dx_dy_sx_sy[3];
	}
}

void	draw_line(t_app *a, t_pt2 p, t_pt2 q, uint32_t color)
{
	int	dx_dy_sx_sy[4];
	int	err;

	dx_dy_sx_sy[0] = int_abs(q.x - p.x);
	dx_dy_sx_sy[1] = int_abs(q.y - p.y);
	init_dirs(&dx_dy_sx_sy[2], &dx_dy_sx_sy[3], p, q);
	err = dx_dy_sx_sy[0] - dx_dy_sx_sy[1];
	while (1)
	{
		put_px(a, p.x, p.y, color);
		if (p.x == q.x && p.y == q.y)
			break ;
		step_line(&p.x, &p.y, &err, dx_dy_sx_sy);
	}
}
