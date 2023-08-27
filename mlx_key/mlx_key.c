/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:36:19 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 00:34:25 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	key_w(t_data *data)
{
	double	newposxw;
	double	newposyw;

	newposxw = data->ray_i->posx + (data->ray_i->dirx * 0.5);
	newposyw = data->ray_i->posy + (data->ray_i->diry * 0.5);
	if (data->map_i->map[(int)newposxw][(int)newposyw] != '1')
	{
		data->ray_i->posx += data->ray_i->dirx * 0.5;
		data->ray_i->posy += data->ray_i->diry * 0.5;
	}
}

void	key_a(t_data *data)
{
	double	newposxa;
	double	newposya;

	newposxa = data->ray_i->posx - (data->ray_i->diry * 0.5);
	newposya = data->ray_i->posy + (data->ray_i->dirx * 0.5);
	if (data->map_i->map[(int)newposxa][(int)newposya] != '1')
	{
		data->ray_i->posx -= data->ray_i->diry * 0.5;
		data->ray_i->posy += data->ray_i->dirx * 0.5;
	}
}

void	key_d(t_data *data)
{
	double	newposxd;
	double	newposyd;

	newposxd = data->ray_i->posx + (data->ray_i->diry * 0.5);
	newposyd = data->ray_i->posy - (data->ray_i->dirx * 0.5);
	if (data->map_i->map[(int)newposxd][(int)newposyd] != '1')
	{
		data->ray_i->posx += data->ray_i->diry * 0.5;
		data->ray_i->posy -= data->ray_i->dirx * 0.5;
	}
}

void	key_s(t_data *data)
{
	double	newposxs;
	double	newposys;

	newposxs = data->ray_i->posx - (data->ray_i->dirx * 0.5);
	newposys = data->ray_i->posy - (data->ray_i->diry * 0.5);
	if (data->map_i->map[(int)newposxs][(int)newposys] != '1')
	{
		data->ray_i->posx -= data->ray_i->dirx * 0.5;
		data->ray_i->posy -= data->ray_i->diry * 0.5;
	}
}

int	handle_input(int key, t_data *data)
{
	if (key == 65307)
		mlx_loop_end(data->mlx_i->mlx);
	else if (key == 'w')
		key_w(data);
	else if (key == 'a')
		key_a(data);
	else if (key == 'd')
		key_d(data);
	else if (key == 's')
		key_s(data);
	else if (key == 65363)
		rotate_player(data, -0.1);
	else if (key == 65361)
		rotate_player(data, 0.1);
	display(data);
	return (0);
}
