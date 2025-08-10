#include "../include/fdf.h"

void clear_img(t_app *a)
{
    int total;
    int i;

    total = a->img->width * a->img->height * 4; /* RGBA */
    i = 0;
    while (i < total)
    {
        a->img->pixels[i++] = 0;   /* R */
        a->img->pixels[i++] = 0;   /* G */
        a->img->pixels[i++] = 0;   /* B */
        a->img->pixels[i++] = 255; /* A (opaque) */
    }
}
uint32_t color_for_edge(int x0, int y0, int x1, int y1, t_app *a)
{

    if (a->shade_on)
        return (uint32_t)shade_line(x0, y0, x1, y1, a);
    (void)x0; (void)y0; (void)x1; (void)y1; (void)a;
    return 0xAAAAAAFF; /* RGBA */
}

void render_scene(t_app *a)
{
    mlx_delete_image(a->mlx, a->img);
    a->img = mlx_new_image(a->mlx, WIN_W, WIN_H);
    mlx_image_to_window(a->mlx, a->img, 0, 0);

    if (a->anim_on)
        apply_animation(&a->map, a->time, 1.0f, 0.5f);

    // gambar tiap edge
    for (int y = 0; y < a->map.h; y++)
    {
        for (int x = 0; x < a->map.w; x++)
        {
            if (x + 1 < a->map.w)
                draw_line(a, project_iso((t_pt3){x, y, a->map.z[y][x]}, a->cam),
                              project_iso((t_pt3){x+1, y, a->map.z[y][x+1]}, a->cam),
                              a->shade_on ? shade_line(x, y, x+1, y, a) : 0xFFFFFF);
            if (y + 1 < a->map.h)
                draw_line(a, project_iso((t_pt3){x, y, a->map.z[y][x]}, a->cam),
                              project_iso((t_pt3){x, y+1, a->map.z[y+1][x]}, a->cam),
                              a->shade_on ? shade_line(x, y, x, y+1, a) : 0xFFFFFF);
        }
    }
    a->time += 0.016f; // kira-kira 60 FPS
}
