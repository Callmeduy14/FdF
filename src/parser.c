/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 06:57:18 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/19 20:00:29 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	process_dims_line(const char *line, int *w, int *h)
{
	char	**tok;
	int		cnt;

	if (line[0] == '\0' || line[0] == '\n')
		return (0);
	tok = ft_split(line, ' ');
	cnt = (int)ft_strarr_len(tok);
	if (*w < 0)
		*w = cnt;
	else if (cnt != *w)
	{
		ft_strarr_free(tok);
		return (-1);
	}
	ft_strarr_free(tok);
	*h = *h + 1;
	return (0);
}

int	pass1_dims(const char *path, int *out_h, int *out_w)
{
	int		fd;
	int		w;
	int		h;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	w = -1;
	h = 0;
	line = get_next_line(fd);
	while (line != 0)
	{
		process_dims_line(line, &w, &h);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	*out_h = h;
	*out_w = w;
	if (h <= 0 || w <= 0)
		return (1);
	return (0);
}

int	parse_fdf(const char *path, t_map *out)
{
	int	err;
	int	w;
	int	h;

	err = pass1_dims(path, &h, &w);
	if (err != 0)
		return (1);
	err = alloc_and_init_map(out, h, w);
	if (err != 0)
		return (1);
	out->min_z = 1000000000.0f;
	out->max_z = -1000000000.0f;
	err = pass2_fill(path, out, w, h);
	if (err != 0)
		return (1);
	return (0);
}
