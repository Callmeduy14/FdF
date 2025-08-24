/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:53:33 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/22 21:15:18 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdint.h>
# include "MLX42/MLX42.h"
# include "libft.h"

# define WIN_W 1200
# define WIN_H 800

/* --------------------- basic types --------------------- */
typedef struct s_pt3
{
	int		x;
	int		y;
	float	z;
}	t_pt3;

typedef struct s_pt2
{
	int			x;
	int			y;
	uint32_t	color;
}	t_pt2;

/* ----------------------- map --------------------------- */
typedef struct s_map
{
	int		w;
	int		h;
	float	**z;
	float	**z0;
	float	min_z;
	float	max_z;
	float	min0;
	float	max0;
}	t_map;

/* ---------------------- camera ------------------------- */
typedef struct s_cam
{
	float	angle;
	float	zscale;
	float	rot_x;
	float	rot_y;
	float	rot_z;
	float	pan_x;
	float	pan_y;
	float	zoom;
	float	pivot_x;
	float	pivot_y;
	float	pivot_z;
}	t_cam;

/* Back-compat (hindari pakai alias; prefer akses field langsung) */
# define OFFX pan_x
# define OFFY pan_y
# define SCALE zoom

/* ----------------------- app --------------------------- */
typedef struct s_app
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		map;
	t_cam		cam;
	int			anim_on;
	int			shade_on;
	float		time;
	int			anim_inited;
	float		last_t;
	int			dragging;
	int			last_x;
	int			last_y;
	int			needs_redraw;
	mlx_image_t	*hud;
}	t_app;

typedef struct s_wave
{
	float	ampl;
	float	speed;
	float	kx;
	float	ky;
	float	cx;
	float	cy;
}	t_wave;

/* -------------------- parsing / utils ------------------ */
int			parse_fdf(const char *path, t_map *out);
int			pass1_dims(const char *path, int *h, int *w);
int			alloc_and_init_map(t_map *out, int h, int w);
int			pass2_fill(const char *path, t_map *out, int w, int h);
int			pass1_dims(const char *path, int *h, int *w);
int			alloc_and_init_map(t_map *out, int h, int w);
int			pass2_fill(const char *path, t_map *out, int w, int h);

void		app_cleanup(t_app *a);
size_t		ft_strarr_len(char **arr);
void		ft_strarr_free(char **arr);
void		panic(t_app *a, const char *msg, int err);

/* ---------------- projection + render ------------------ */
t_pt2		project_iso(t_pt3 p, t_cam c);
void		render_scene(t_app *a);
void		render_pivot(t_app *a);
void		draw_line(t_app *a, t_pt2 p, t_pt2 q, uint32_t color);
void		draw_grid_row(t_app *a, int y);
uint32_t	shade_line(t_pt2 p0, t_pt2 p1, t_app *a);
uint32_t	height_color(float z, const t_map *m);

/* --------------------- animation ----------------------- */
void		anim_reset_clock(t_app *a, float t0);
void		apply_animation(t_app *a, float t, float ampl, float speed);

/* ----------------------- events ------------------------ */
void		events_init(t_app *a);
void		handle_center_pivot(mlx_key_data_t k, t_app *a);
void		handle_pan_zoom(mlx_key_data_t k, t_app *a);
void		handle_toggles(mlx_key_data_t k, t_app *a);
void		handle_angle(mlx_key_data_t k, t_app *a);
void		handle_rot_keys(mlx_key_data_t k, t_app *a);
void		fit_to_view(t_app *a);
void		handle_reset_key(mlx_key_data_t k, t_app *a);
void		handle_height_keys(mlx_key_data_t k, t_app *a);
void		pply_mouse_rotation_drag(t_app *app, int dx, int dy);
void		apply_mouse_pan_drag(t_app *app, int dx, int dy);
float		compute_fit_zoom(t_app *a);

/* map baseline helpers */
int			map_clone_base(t_map *m);
void		map_restore_base(t_map *m);

/* --------------------- app init ------------------------ */
int			init_app(t_app *a, const char *path);
int			init_window_and_image(t_app *a);
void		set_pivot_center(t_app *a);
void		init_cam(t_cam *c);

#endif
