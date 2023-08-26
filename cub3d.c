/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 03:00:15 by abrin             #+#    #+#             */
/*   Updated: 2023/08/25 22:15:59 by abrin            ###   ########.fr       */
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
	data->mlx_i2 = gc_malloc(&data->gc, sizeof(t_mlx));
	data->map_i->x_wall = 0;
	data->map_i->y_wall = 1;
	data->map_i->map_error = 0;
	data->map_i->trace = 0;
}

void	init_ray(t_data *data)
{
	data->ray_i->screen_w = 1280;
	data->ray_i->screen_h = 720;
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
void	rotate_player(t_data *data, double angle)
{
	double	old_dirX;
	double	old_planeX;

	old_dirX = data->ray_i->dirX;
	old_planeX = data->ray_i->planeX;
	data->ray_i->dirX = (old_dirX * cos(angle)) - (data->ray_i->dirY * sin(angle));
	data->ray_i->dirY = (old_dirX * sin(angle)) + (data->ray_i->dirY * cos(angle));
	data->ray_i->planeX = (old_planeX * cos(angle)) - (data->ray_i->planeY * sin(angle));
	data->ray_i->planeY = (old_planeX * sin(angle)) + (data->ray_i->planeY * cos(angle));
}


int	handle_input(int key, t_data *data)
{
	int	w;
	int	h;

	if (key == 65307)
	{
		mlx_destroy_window(data->mlx_i->mlx, data->mlx_i->mlx_win);
		gc_clean(&data->gc);
		exit(0);
	}
	else if (key == 'w')
	{
		data->mlx_i2->img = mlx_xpm_file_to_image (data->mlx_i2->mlx, "img/grey2.xpm", &w, &h);
		mlx_put_image_to_window(data->mlx_i2->mlx, data->mlx_i2->mlx_win, data->mlx_i2->img, data->ray_i->posY * 32, data->ray_i->posX * 32);
		double newPosXw = data->ray_i->posX + (data->ray_i->dirX * 0.5);
		double newPosYw = data->ray_i->posY + (data->ray_i->dirY * 0.5);
		if (data->map_i->map[(int)newPosXw][(int)newPosYw] != '1')
		{
			data->ray_i->posX += data->ray_i->dirX * 0.5;
			data->ray_i->posY += data->ray_i->dirY * 0.5;
		}
	}
	else if (key == 'a')
	{
		data->mlx_i2->img = mlx_xpm_file_to_image (data->mlx_i2->mlx, "img/grey2.xpm", &w, &h);
		mlx_put_image_to_window(data->mlx_i2->mlx, data->mlx_i2->mlx_win, data->mlx_i2->img, data->ray_i->posY * 32, data->ray_i->posX * 32);
		double newPosXa = data->ray_i->posX - (data->ray_i->dirY * 0.5);
		double newPosYa = data->ray_i->posY + (data->ray_i->dirX * 0.5);
		if (data->map_i->map[(int)newPosXa][(int)newPosYa] != '1')
		{
			data->ray_i->posX -= data->ray_i->dirY * 0.5;
			data->ray_i->posY += data->ray_i->dirX * 0.5;
		}
	}
	else if (key == 'd')
	{
		data->mlx_i2->img = mlx_xpm_file_to_image (data->mlx_i2->mlx, "img/grey2.xpm", &w, &h);
		mlx_put_image_to_window(data->mlx_i2->mlx, data->mlx_i2->mlx_win, data->mlx_i2->img, data->ray_i->posY * 32, data->ray_i->posX * 32);
		double newPosXd = data->ray_i->posX + (data->ray_i->dirY * 0.5);
		double newPosYd = data->ray_i->posY - (data->ray_i->dirX * 0.5);
		if (data->map_i->map[(int)newPosXd][(int)newPosYd] != '1')
		{
			data->ray_i->posX += data->ray_i->dirY * 0.5;
			data->ray_i->posY -= data->ray_i->dirX * 0.5;
		}
	}
	else if (key == 's')
	{
		data->mlx_i2->img = mlx_xpm_file_to_image (data->mlx_i2->mlx, "img/grey2.xpm", &w, &h);
		mlx_put_image_to_window(data->mlx_i2->mlx, data->mlx_i2->mlx_win, data->mlx_i2->img, data->ray_i->posY * 32, data->ray_i->posX * 32);
		double newPosXs = data->ray_i->posX - (data->ray_i->dirX * 0.5);
		double newPosYs = data->ray_i->posY - (data->ray_i->dirY * 0.5);
		if (data->map_i->map[(int)newPosXs][(int)newPosYs] != '1')
		{
			data->ray_i->posX -= data->ray_i->dirX * 0.5;
			data->ray_i->posY -= data->ray_i->dirY * 0.5;
		}
	}
	else if (key == 65363)
		rotate_player(data, -0.1);
	else if (key == 65361)
		rotate_player(data, 0.1);
	display(data);
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;

	(void)argc;
	gc_init(&data.gc);
	init(&data);
	data.mlx_i->mlx = mlx_init();
	data.mlx_i2->mlx = mlx_init();
	get_map(&data, argv[1]);
	if (check_error(&data, argv[1]) == 1)
		return(-1);
	for (size_t i = 0; i < 13; i++)
	{
		printf("%s-*\n", data.map_i->map[i]);
	}

	init_ray(&data);
	setup_texture(&data);
	data.mlx_i->mlx_win = mlx_new_window(data.mlx_i->mlx, data.ray_i->screen_w, data.ray_i->screen_h, "cub3d");
	data.mlx_i2->mlx_win = mlx_new_window(data.mlx_i2->mlx, data.x_map * 32, data.y_map * 32, "minimap");
	data.mlx_i->img = mlx_new_image(data.mlx_i->mlx, data.ray_i->screen_w, data.ray_i->screen_h);
	data.mlx_i->img_addr = mlx_get_data_addr(data.mlx_i->img, &(data.mlx_i->bpp), &(data.mlx_i->line_len), &(data.mlx_i->endian));
	draw_map2D(&data);
	mlx_key_hook(data.mlx_i->mlx_win, &handle_input, &data);
	//mlx_hook(data.mlx_i->mlx_win, 17, 1L << 0, handle_mouse, &data);
	//mlx_expose_hook(data.mlx_i->mlx_win, display, &data);
	mlx_loop(data.mlx_i->mlx);
}
