/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 06:59:51 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/18 06:59:52 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_partial_rows(float **rows, int up_to)
{
	int	i;

	i = 0;
	while (i < up_to)
	{
		free(rows[i]);
		i = i + 1;
	}
	free(rows);
}

static int	alloc_z0(t_map *m)
{
	int	i;

	m->z0 = (float **)malloc(sizeof(float *) * m->h);
	if (m->z0 == 0)
		return (1);
	i = 0;
	while (i < m->h)
	{
		m->z0[i] = (float *)malloc(sizeof(float) * m->w);
		if (m->z0[i] == 0)
		{
			free_partial_rows(m->z0, i);
			m->z0 = 0;
			return (1);
		}
		i = i + 1;
	}
	return (0);
}

static void	copy_row(float *dst, float *src, int w)
{
	int	j;

	j = 0;
	while (j < w)
	{
		dst[j] = src[j];
		j = j + 1;
	}
}

int	map_clone_base(t_map *m)
{
	int	i;

	if (alloc_z0(m) != 0)
		return (1);
	i = 0;
	while (i < m->h)
	{
		copy_row(m->z0[i], m->z[i], m->w);
		i = i + 1;
	}
	m->min0 = m->min_z;
	m->max0 = m->max_z;
	return (0);
}

void	map_restore_base(t_map *m)
{
	int	i;

	if (m->z0 == 0)
		return ;
	i = 0;
	while (i < m->h)
	{
		copy_row(m->z[i], m->z0[i], m->w);
		i = i + 1;
	}
	m->min_z = m->min0;
	m->max_z = m->max0;
}
