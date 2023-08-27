/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:26:15 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 02:26:46 by abrin            ###   ########.fr       */
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
	data->map_i->trace = 0;
}

void	init_ray(t_data *data)
{
	data->ray_i->screen_w = 1280;
	data->ray_i->screen_h = 720;
	data->ray_i->dirx = -1;
	data->ray_i->diry = 0;
	data->ray_i->planex = 0;
	data->ray_i->planey = 0.66;
	data->ray_i->time = 0;
	data->ray_i->oldtime = 0;
}
