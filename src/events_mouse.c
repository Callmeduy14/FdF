/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:57:40 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/23 11:52:08 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	apply_drag_rotation(t_app *app, int dx, int dy)
{
	if (mlx_is_key_down(app->mlx, MLX_KEY_X))
		app->cam.rot_x += (float)dy * 0.005f;
	else if (mlx_is_key_down(app->mlx, MLX_KEY_Y))
		app->cam.rot_y += (float)dx * 0.005f;
	else if (mlx_is_key_down(app->mlx, MLX_KEY_Z))
		app->cam.rot_z += (float)dx * 0.005f;
	else
	{
		app->cam.rot_y += (float)dx * 0.005f;
		app->cam.rot_x += (float)dy * 0.005f;
	}
}

static void	apply_drag_pan(t_app *app, int dx, int dy)
{
	app->cam.pan_x += (float)dx;
	app->cam.pan_y += (float)dy;
}

void	on_mouse_move(double xpos, double ypos, void *param)
{
	t_app	*app;
	int		dx;
	int		dy;

	app = (t_app *)param;
	if (!app->dragging)
		return ;
	dx = (int)xpos - app->last_x;
	dy = (int)ypos - app->last_y;
	if (mlx_is_mouse_down(app->mlx, MLX_MOUSE_BUTTON_LEFT))
		apply_drag_rotation(app, dx, dy);
	else if (mlx_is_mouse_down(app->mlx, MLX_MOUSE_BUTTON_RIGHT))
		apply_drag_pan(app, dx, dy);
	app->last_x = (int)xpos;
	app->last_y = (int)ypos;
	app->needs_redraw = 1;
}

void	on_mouse_down(mouse_key_t b, action_t axt, modifier_key_t m, void *p)
{
	t_app	*app;

	(void)m;
	app = (t_app *)p;
	if (axt == MLX_PRESS
		&& (b == MLX_MOUSE_BUTTON_LEFT || b == MLX_MOUSE_BUTTON_RIGHT))
	{
		app->dragging = 1;
		mlx_get_mouse_pos(app->mlx, &app->last_x, &app->last_y);
	}
	if (axt == MLX_RELEASE
		&& (b == MLX_MOUSE_BUTTON_LEFT || b == MLX_MOUSE_BUTTON_RIGHT))
		app->dragging = 0;
}
