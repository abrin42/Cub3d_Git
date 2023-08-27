/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 03:00:15 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 03:30:02 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_mouse(int mouse, t_data *data)

{
	(void)mouse;
	(void)data;
	exit(0);
	return (0);
}

void	rotate_player(t_data *data, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->ray_i->dirx;
	old_planex = data->ray_i->planex;
	data->ray_i->dirx = (old_dirx * cos
			(angle)) - (data->ray_i->diry * sin(angle));
	data->ray_i->diry = (old_dirx * sin
			(angle)) + (data->ray_i->diry * cos(angle));
	data->ray_i->planex = (old_planex * cos
			(angle)) - (data->ray_i->planey * sin(angle));
	data->ray_i->planey = (old_planex * sin
			(angle)) + (data->ray_i->planey * cos(angle));
}

void	clean_all(t_data *data, int err)
{
	if (data->mlx_i->img != NULL)
		mlx_destroy_image(data->mlx_i->mlx, data->mlx_i->img);
	if (data->map_i->no.img != NULL)
		mlx_destroy_image(data->mlx_i->mlx, data->map_i->no.img);
	if (data->map_i->so.img != NULL)
		mlx_destroy_image(data->mlx_i->mlx, data->map_i->so.img);
	if (data->map_i->ea.img != NULL)
		mlx_destroy_image(data->mlx_i->mlx, data->map_i->ea.img);
	if (data->map_i->we.img != NULL)
		mlx_destroy_image(data->mlx_i->mlx, data->map_i->we.img);
	if (data->mlx_i->mlx_win != NULL)
		mlx_destroy_window(data->mlx_i->mlx, data->mlx_i->mlx_win);
	if (data->mlx_i->mlx != NULL)
		mlx_destroy_display(data->mlx_i->mlx);
	free(data->mlx_i->mlx);
	gc_clean(&data->gc);
	exit(err);
}

void	clean_all_error(t_data *data, int err)
{
	if (data->mlx_i->mlx != NULL)
		mlx_destroy_display(data->mlx_i->mlx);
	free(data->mlx_i->mlx);
	gc_clean(&data->gc);
	exit(err);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	gc_init(&data.gc);
	init(&data);
	data.mlx_i->mlx = mlx_init();
	init_ray(&data);
	get_map(&data, argv[1]);
	if (check_error(&data, argv[1]) == 1)
		clean_all_error(&data, 0);
	setup_texture(&data);
	data.mlx_i->mlx_win = mlx_new_window(data.mlx_i->mlx,
			data.ray_i->screen_w, data.ray_i->screen_h, "cub3d");
	data.mlx_i->img = mlx_new_image(data.mlx_i->mlx,
			data.ray_i->screen_w, data.ray_i->screen_h);
	data.mlx_i->img_addr = mlx_get_data_addr(data.mlx_i->img,
			&(data.mlx_i->bpp), &(data.mlx_i->line_len), &(data.mlx_i->endian));
	mlx_key_hook(data.mlx_i->mlx_win, &handle_input, &data);
	mlx_hook(data.mlx_i->mlx_win, 17, 1L << 0, mlx_loop_end, data.mlx_i->mlx);
	mlx_expose_hook(data.mlx_i->mlx_win, display, &data);
	mlx_loop(data.mlx_i->mlx);
	clean_all(&data, 0);
	return (0);
}
