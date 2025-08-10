#include "../include/fdf.h"

static void on_key(mlx_key_data_t keydata, void *param)
{
    t_app *a = (t_app *)param;
    if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
        return;

    if (keydata.key == MLX_KEY_ESCAPE) {
        mlx_close_window(a->mlx);
        return;
    }
    else if (keydata.key == MLX_KEY_LEFT)  a->cam.offx -= 20;
    else if (keydata.key == MLX_KEY_RIGHT) a->cam.offx += 20;
    else if (keydata.key == MLX_KEY_UP)    a->cam.offy -= 20;
    else if (keydata.key == MLX_KEY_DOWN)  a->cam.offy += 20;
    else if (keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_KP_ADD)      a->cam.scale *= 1.1f;
    else if (keydata.key == MLX_KEY_MINUS || keydata.key == MLX_KEY_KP_SUBTRACT) a->cam.scale *= 0.9f;
    else if (keydata.key == MLX_KEY_A) a->anim_on  = !a->anim_on;
    else if (keydata.key == MLX_KEY_Z) a->shade_on = !a->shade_on;
    render_scene(a); // redraw instan setiap input
}

int key_hook_init(t_app *a)
{
    mlx_key_hook(a->mlx, on_key, a);
    return 0;
}
