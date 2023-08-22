/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 03:00:15 by abrin             #+#    #+#             */
/*   Updated: 2023/08/22 04:53:19 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *data)
{
	data->x_malloc_map = 0;
	data->y_mallocc_map = 0;
	data->map_info = gc_malloc(&data->gc, sizeof(t_map));
	data->ray_i = gc_malloc(&data->gc, sizeof(t_ray));
	data->mlx_i = gc_malloc(&data->gc, sizeof(t_mlx));
	data->map_info->x_wall = 0;
	data->map_info->y_wall = 1;
	data->map_info->map_error = 0;
}

void	init_ray(t_data *data)
{
	data->ray_i->screen_w = data->x_malloc_map * 32;
	data->ray_i->screen_h = data->y_mallocc_map * 32;
	data->ray_i->dirX = -1;
	data->ray_i->dirY = 0;
	data->ray_i->planeX = 0;
	data->ray_i->planeY = 0.66;
	data->ray_i->time = 0;
	data->ray_i->oldTime = 0;
}

int	handle_mouse(int mouse, t_data *data)
{
	(void)mouse;
	(void)data;
		exit(0);
	return (0);
}

int	handle_input(int key, t_data *data)
{
	if (key == 65307)
	{
		mlx_destroy_window(data->mlx_i->mlx, data->mlx_i->mlx_win);
		exit(0);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;

	(void)argc;
	gc_init(&data.gc);
	init(&data);
	get_map(&data, argv[1]);
	init_ray(&data);
	printf("ICI W : %d et H : %d\n", data.ray_i->screen_w, data.ray_i->screen_h);
	check_border_map(&data);
	data.mlx_i->mlx = mlx_init();
	data.mlx_i->mlx_win = mlx_new_window(data.mlx_i->mlx, data.ray_i->screen_w, data.ray_i->screen_h, "cub3d");
	display(&data);
	for (int i = 0; i < data.y_mallocc_map; i++)
	{
		printf("%s\n", data.map_info->map[i]);
	}

	mlx_key_hook(data.mlx_i->mlx_win, &handle_input, &data);
	mlx_hook(data.mlx_i->mlx_win, 17, 1L << 0, handle_mouse, &data);
	mlx_expose_hook(data.mlx_i->mlx_win, display, &data);
	mlx_loop(data.mlx_i->mlx);
}
