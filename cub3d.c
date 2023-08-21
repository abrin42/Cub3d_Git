/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 03:00:15 by abrin             #+#    #+#             */
/*   Updated: 2023/08/22 00:25:43 by tmarie           ###   ########.fr       */
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
	data.mlx_i->mlx = mlx_init();
	data.mlx_i->mlx_win = mlx_new_window(data.mlx_i->mlx, data.x_malloc_map * 32, data.y_mallocc_map * 32, "mlx 42");
	printf("ICI TAILLE MAP X : %d et Y : %d\n", data.x_malloc_map, data.y_mallocc_map);
	for (size_t i = 0; (int)i < data.y_mallocc_map; i++)
	{
		printf("%s\n", data.map_info->map[i]);
	}
	mlx_key_hook(data.mlx_i->mlx_win, &handle_input, &data);
	mlx_hook(data.mlx_i->mlx_win, 17, 1L << 0, handle_mouse, &data);
	mlx_loop(data.mlx_i->mlx);
}
