/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_dispatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:48:54 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/23 11:51:51 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_at_cursor(t_app *a, float factor, int cx, int cy)
{
	const float	old = a->cam.zoom;
	float		new;
	float		eff;

	new = old * factor;
	if (new < 0.05f)
		new = 0.05f;
	if (new > 200.0f)
		new = 200.0f;
	eff = new / old;
	if (fabsf(eff - 1.0f) < 1e-6f)
		return ;
	a->cam.pan_x = (float)cx - eff * ((float)cx - a->cam.pan_x);
	a->cam.pan_y = (float)cy - eff * ((float)cy - a->cam.pan_y);
	a->cam.zoom = new;
	a->needs_redraw = 1;
}

void	on_scroll(double xdelta, double ydelta, void *param)
{
	t_app	*a;
	int32_t	mx;
	int32_t	my;
	float	factor;

	a = (t_app *)param;
	(void)xdelta;
	mlx_get_mouse_pos(a->mlx, &mx, &my);
	if (ydelta > 0.0)
		factor = 1.10f;
	else if (ydelta < 0.0)
		factor = 1.0f / 1.10f;
	else
		return ;
	zoom_at_cursor(a, factor, (int)mx, (int)my);
}

void	on_key(mlx_key_data_t keydata, void *param)
{
	t_app	*a;

	a = (t_app *)param;
	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(a->mlx);
		return ;
	}
	handle_center_pivot(keydata, a);
	handle_pan_zoom(keydata, a);
	handle_toggles(keydata, a);
	handle_angle(keydata, a);
	handle_reset_key(keydata, a);
	handle_rot_keys(keydata, a);
	handle_height_keys(keydata, a);
	a->needs_redraw = 1;
}
