/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:57:47 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/23 11:52:20 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_reset_key(mlx_key_data_t k, t_app *a)
{
	if (k.key == MLX_KEY_R)
	{
		init_cam(&a->cam);
		set_pivot_center(a);
		fit_to_view(a);
		a->needs_redraw = 1;
	}
}

void	set_pivot_center(t_app *a)
{
	a->cam.pivot_x = ((float)(a->map.w - 1)) * 0.5f;
	a->cam.pivot_y = ((float)(a->map.h - 1)) * 0.5f;
	a->cam.pivot_z = 0.0f;
}
