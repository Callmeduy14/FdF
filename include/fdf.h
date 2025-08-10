#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdint.h>
# include "MLX42/MLX42.h"
# include "libft.h"              /* karena libft ada di include/libft, pastikan -Iinclude sudah ada di Makefile */

# define WIN_W 1200
# define WIN_H 800

/* ---- basic types ---- */
typedef struct s_pt3
{
	int     x;
	int     y;
	float   z;
}   t_pt3;

typedef struct s_pt2
{
	int         x;
	int         y;
	uint32_t    color;     /* RGBA untuk MLX42 */
}   t_pt2;

typedef struct s_map
{
	int     w;
	int     h;
	float **z;
}   t_map;

typedef struct s_cam
{
	float   angle;
	float   scale;
	float   zscale;
	int     offx;
	int     offy;
}   t_cam;

/* ---- app context (MLX42) ---- */
typedef struct s_app
{
	mlx_t       *mlx;       /* context & window (MLX42) */
	mlx_image_t *img;       /* target gambar */
	t_map       map;
	t_cam       cam;
	int         anim_on;
	int         shade_on;
	float       time;
}   t_app;

/* ---- API ---- */
/* parsing */
int     parse_fdf(const char *path, t_map *out);

/* iso projection (MANDATORY) */
t_pt2   project_iso(t_pt3 p, t_cam c);

/* render & drawing */
void    render_scene(t_app *a);
void    draw_line(t_app *a, t_pt2 p, t_pt2 q, uint32_t color);

/* events (MLX42) */
int     key_hook_init(t_app *a);   /* panggil setelah image ditempel ke window dengan mlx_image_to_window */

/* cleanup */
void    free_map(t_map *m);

/* utils utk hasil ft_split */
size_t     ft_strarr_len(char **arr);
void    ft_strarr_free(char **arr);
void 	app_cleanup(t_app *a);
void 	panic(t_app *a, const char *msg, int err);

uint32_t    shade_line(int x0, int y0, int x1, int y1, t_app *a);
void        apply_animation(t_map *m, float t, float ampl, float freq);


#endif /* FDF_H */
