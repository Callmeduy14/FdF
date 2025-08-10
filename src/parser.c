#include "../include/fdf.h"

static int	alloc_map(t_map *m, int h, int w)
{
	int	i;

	m->h = h;
	m->w = w;
	m->z = (float **)malloc(sizeof(float *) * h);
	if (!m->z)
		return (1);
	i = 0;
	while (i < h)
	{
		m->z[i] = (float *)malloc(sizeof(float) * w);
		if (!m->z[i])
			return (1);
		i++;
	}
	return (0);
}

static int	fill_row(float *row, char **tok, int w)
{
	int	i;

	i = 0;
	while (i < w)
	{
		row[i] = (float)atoi(tok[i]);
		i++;
	}
	return (0);
}

int	parse_fdf(const char *path, t_map *out)
{
	int		fd;
	int		w;
	int		h;
	char	*line;
	char	**tok;
	int		i;

	fd = open(path, 0);
	if (fd < 0)
		return (1);
	w = -1;
	h = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\0' && line[0] != '\n')
		{
			tok = ft_split(line, ' ');
			if (w < 0)
				w = ft_strarr_len(tok);
			h++;
			ft_strarr_free(tok);
		}
		free(line);
	}
	close(fd);
	if (w <= 0 || h <= 0)
		return (1);
	if (alloc_map(out, h, w))
		return (1);
	fd = open(path, 0);
	if (fd < 0)
		return (1);
	i = 0;
	while (i < h)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\n')
			continue ;
		tok = ft_split(line, ' ');
		fill_row(out->z[i], tok, w);
		ft_strarr_free(tok);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
