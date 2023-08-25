/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 03:00:15 by abrin             #+#    #+#             */
/*   Updated: 2023/08/25 03:56:22 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *data)
{
	data->x_map = 0;
	data->y_map = 0;
	data->map_i = gc_malloc(&data->gc, sizeof(t_map));
	data->ray_i = gc_malloc(&data->gc, sizeof(t_ray));
	data->mlx_i = gc_malloc(&data->gc, sizeof(t_mlx));
	data->map_i->x_wall = 0;
	data->map_i->y_wall = 1;
	data->map_i->map_error = 0;
}

void	init_ray(t_data *data)
{
	data->ray_i->screen_w = data->x_map * 32;
	data->ray_i->screen_h = data->y_map * 32;
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
	data.mlx_i->mlx = mlx_init();
	get_map(&data, argv[1]);
	//if (check_error(&data, argv[1]) == 1)
	//	return(-1);
	init_ray(&data);
	printf("ICI W : %d et H : %d\n", data.ray_i->screen_w, data.ray_i->screen_h);
	setup_texture(&data);
	data.mlx_i->mlx_win = mlx_new_window(data.mlx_i->mlx, data.ray_i->screen_w, data.ray_i->screen_h, "cub3d");
	data.mlx_i->img = mlx_new_image(data.mlx_i->mlx, data.ray_i->screen_w, data.ray_i->screen_h);
	data.mlx_i->img_addr = mlx_get_data_addr(data.mlx_i->img, &(data.mlx_i->bpp), &(data.mlx_i->line_len), &(data.mlx_i->endian));
	mlx_key_hook(data.mlx_i->mlx_win, &handle_input, &data);
	mlx_hook(data.mlx_i->mlx_win, 17, 1L << 0, handle_mouse, &data);
	mlx_expose_hook(data.mlx_i->mlx_win, display, &data);
	mlx_loop(data.mlx_i->mlx);
}
