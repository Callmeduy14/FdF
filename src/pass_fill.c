/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 06:55:04 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/22 19:49:59 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fill_row(float *row, char **tok, int w, t_map *m)
{
	int		i;
	float	v;

	i = 0;
	while (i < w)
	{
		v = (float)ft_atoi(tok[i]);
		row[i] = v;
		if (v < m->min_z)
			m->min_z = v;
		if (v > m->max_z)
			m->max_z = v;
		i = i + 1;
	}
}

static int	is_line_data(const char *line)
{
	if (line[0] == '\n' || line[0] == '\0')
		return (0);
	return (1);
}

static int	process_line(t_map *m, const char *line, int w, int i)
{
	char	**tok;
	int		ok;

	ok = 0;
	tok = ft_split(line, ' ');
	if ((int)ft_strarr_len(tok) != w)
		ok = 1;
	else
		fill_row(m->z[i], tok, w, m);
	ft_strarr_free(tok);
	return (ok);
}

static int	read_rows(t_map *m, int fd, int w, int h)
{
	int		i;
	char	*line;
	int		err;

	i = 0;
	line = get_next_line(fd);
	while (line != 0 && i < h)
	{
		if (is_line_data(line))
		{
			err = process_line(m, line, w, i);
			if (err != 0)
			{
				free(line);
				return (1);
			}
			i = i + 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	pass2_fill(const char *path, t_map *m, int w, int h)
{
	int	fd;
	int	err;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	err = read_rows(m, fd, w, h);
	close(fd);
	if (err != 0)
		return (1);
	return (0);
}
