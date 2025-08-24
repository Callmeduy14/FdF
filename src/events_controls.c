/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 07:08:49 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/22 21:41:26 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clamp_angle(t_cam *c)
{
	if (c->angle < 0.20f)
		c->angle = 0.20f;
	if (c->angle > 1.20f)
		c->angle = 1.20f;
}

void	handle_pan_zoom(mlx_key_data_t k, t_app *a)
{
	if (k.key == MLX_KEY_RIGHT)
		a->cam.pan_x -= 20.0f;
	else if (k.key == MLX_KEY_LEFT)
		a->cam.pan_x += 20.0f;
	else if (k.key == MLX_KEY_DOWN)
		a->cam.pan_y -= 20.0f;
	else if (k.key == MLX_KEY_UP)
		a->cam.pan_y += 20.0f;
	else if (k.key == MLX_KEY_EQUAL || k.key == MLX_KEY_KP_ADD)
		a->cam.zoom *= 1.10f;
	else if (k.key == MLX_KEY_MINUS || k.key == MLX_KEY_KP_SUBTRACT)
		a->cam.zoom *= 0.90f;
	if (a->cam.zoom < 0.05f)
		a->cam.zoom = 0.05f;
}

void	handle_toggles(mlx_key_data_t k, t_app *a)
{
	if (k.key == MLX_KEY_A)
		a->anim_on = !a->anim_on;
	else if (k.key == MLX_KEY_Z)
		a->shade_on = !a->shade_on;
}

void	handle_angle(mlx_key_data_t k, t_app *a)
{
	if (k.key == MLX_KEY_LEFT_BRACKET)
	{
		a->cam.angle -= 0.03f;
		clamp_angle(&a->cam);
	}
	else if (k.key == MLX_KEY_RIGHT_BRACKET)
	{
		a->cam.angle += 0.03f;
		clamp_angle(&a->cam);
	}
	else if (k.key == MLX_KEY_1)
		a->cam.angle = (float)(M_PI / 6.0f);
	else if (k.key == MLX_KEY_2)
		a->cam.angle = 0.6154797f;
	else if (k.key == MLX_KEY_3)
		a->cam.angle = (float)(M_PI / 4.0f);
}

void	handle_rot_keys(mlx_key_data_t k, t_app *a)
{
	if (k.key == MLX_KEY_Q)
		a->cam.rot_z -= 0.05f;
	else if (k.key == MLX_KEY_E)
		a->cam.rot_z += 0.05f;
}
