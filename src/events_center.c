/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_center.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:45:44 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/22 20:26:47 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clamp_pivot_xy(t_app *a)
{
	if (a->cam.pivot_x < 0.0f)
		a->cam.pivot_x = 0.0f;
	if (a->cam.pivot_x > (float)(a->map.w - 1))
		a->cam.pivot_x = (float)(a->map.w - 1);
	if (a->cam.pivot_y < 0.0f)
		a->cam.pivot_y = 0.0f;
	if (a->cam.pivot_y > (float)(a->map.h - 1))
		a->cam.pivot_y = (float)(a->map.h - 1);
}

float	compute_fit_zoom(t_app *a)
{
	float	span_xy;
	float	span_z;
	float	zw;
	float	zh;

	span_xy = ((float)(a->map.w + a->map.h)) * 0.5f;
	if (span_xy < 1.0f)
		span_xy = 1.0f;
	span_z = (a->map.max_z - a->map.min_z) * a->cam.zscale;
	zw = ((float)WIN_W - 60.0f) / (span_xy * 2.0f * cosf(a->cam.angle));
	zh = ((float)WIN_H - 60.0f)
		/ (span_xy * 2.0f * sinf(a->cam.angle) + span_z);
	if (zw < 0.05f)
		zw = 0.05f;
	if (zh < 0.05f)
		zh = 0.05f;
	if (zw < zh)
		return (zw);
	return (zh);
}

void	fit_to_view(t_app *a)
{
	a->cam.zoom = compute_fit_zoom(a) * 0.70f;
	a->cam.pan_x = (float)(WIN_W / 2);
	a->cam.pan_y = (float)(WIN_H * 0.45f);
}

void	handle_center_pivot(mlx_key_data_t k, t_app *a)
{
	if (k.key == MLX_KEY_C)
	{
		a->cam.pan_x = (float)(WIN_W / 2);
		a->cam.pan_y = (float)(WIN_H / 2);
	}
	else if (k.key == MLX_KEY_F)
		fit_to_view(a);
	else if (k.key == MLX_KEY_G)
	{
		a->cam.pivot_x = ((float)(a->map.w - 1)) * 0.5f;
		a->cam.pivot_y = ((float)(a->map.h - 1)) * 0.5f;
		a->cam.pivot_z = 0.0f;
	}
	else if (k.key == MLX_KEY_J)
		a->cam.pivot_x -= 1.0f;
	else if (k.key == MLX_KEY_L)
		a->cam.pivot_x += 1.0f;
	else if (k.key == MLX_KEY_I)
		a->cam.pivot_y -= 1.0f;
	else if (k.key == MLX_KEY_K)
		a->cam.pivot_y += 1.0f;
	clamp_pivot_xy(a);
}
