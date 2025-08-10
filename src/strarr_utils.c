#include "../include/fdf.h"

size_t ft_strarr_len(char **arr)
{
    size_t i = 0;
    if (!arr)
        return 0;
    while (arr[i])
        i++;
    return i;
}

void ft_strarr_free(char **arr)
{
    size_t i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}
