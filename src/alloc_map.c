/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 06:57:03 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/18 06:57:04 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_partial(float **z, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(z[i]);
		i = i + 1;
	}
	free(z);
}

int	alloc_and_init_map(t_map *m, int h, int w)
{
	int	i;

	m->h = h;
	m->w = w;
	m->z = (float **)malloc(sizeof(float *) * h);
	if (m->z == 0)
		return (1);
	i = 0;
	while (i < h)
	{
		m->z[i] = (float *)malloc(sizeof(float) * w);
		if (m->z[i] == 0)
		{
			free_partial(m->z, i);
			m->z = 0;
			return (1);
		}
		i = i + 1;
	}
	return (0);
}
