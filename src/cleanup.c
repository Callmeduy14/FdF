/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:39:56 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/18 01:39:57 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *m)
{
	int	i;

	if (!m || !m->z)
		return ;
	i = 0;
	while (i < m->h)
	{
		free(m->z[i]);
		i++;
	}
	free(m->z);
	m->z = 0;
}

void	app_cleanup(t_app *a)
{
	if (!a)
		return ;
	if (a->img)
		mlx_delete_image(a->mlx, a->img);
	if (a->mlx)
		mlx_terminate(a->mlx);
	free_map(&a->map);
}

void	panic(t_app *a, const char *msg, int err)
{
	if (msg)
		write(2, msg, (int)ft_strlen(msg));
	app_cleanup(a);
	if (err)
		exit(err);
}
