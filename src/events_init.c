/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:57:04 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/18 01:57:05 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	on_key(mlx_key_data_t keydata, void *param);
void	on_mouse_move(double xpos, double ypos, void *param);
void	on_mouse_down(mouse_key_t b, action_t axt, modifier_key_t m, void *p);
void	on_scroll(double xdelta, double ydelta, void *param);

void	events_init(t_app *a)
{
	mlx_key_hook(a->mlx, on_key, a);
	mlx_cursor_hook(a->mlx, on_mouse_move, a);
	mlx_mouse_hook(a->mlx, on_mouse_down, a);
	mlx_scroll_hook(a->mlx, on_scroll, a);
}
