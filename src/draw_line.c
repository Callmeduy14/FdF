#include "../include/fdf.h"

static void put_px(t_app *a, int x, int y, uint32_t color)
{
    if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
        return ;
    mlx_put_pixel(a->img, x, y, color);
}

/* Bresenham line — warna RGBA (uint32_t) sesuai fdf.h */
void    draw_line(t_app *a, t_pt2 p, t_pt2 q, uint32_t color)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;

    dx = (q.x > p.x) ? q.x - p.x : p.x - q.x;
    dy = (q.y > p.y) ? q.y - p.y : p.y - q.y;
    sx = (p.x < q.x) ? 1 : -1;
    sy = (p.y < q.y) ? 1 : -1;
    err = dx - dy;
    while (1)
    {
        put_px(a, p.x, p.y, color);
        if (p.x == q.x && p.y == q.y)
            break ;
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; p.x += sx; }
        if (e2 <  dx) { err += dx; p.y += sy; }
    }
}
