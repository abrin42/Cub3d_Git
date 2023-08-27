/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:44:41 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 03:17:24 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_texture	*step_x(t_data *data)
{
	t_texture	*text;

	text = NULL;
	data->ray_i->sidedistx += data->ray_i->deltadistx;
	data->ray_i->mapx += data->ray_i->stepx;
	data->ray_i->side = 0;
	if (data->map_i->map[data->ray_i->mapx][data->ray_i->mapy] != '0')
	{
		if (data->ray_i->stepx > 0)
			text = &(data->map_i->so);
		else
			text = &(data->map_i->no);
	}
	return (text);
}

static t_texture	*step_y(t_data *data)
{
	t_texture	*text;

	text = NULL;
	data->ray_i->sidedisty += data->ray_i->deltadisty;
	data->ray_i->mapy += data->ray_i->stepy;
	data->ray_i->side = 1;
	if (data->map_i->map[data->ray_i->mapx][data->ray_i->mapy] != '0')
	{
		if (data->ray_i->stepy > 0)
			text = &(data->map_i->ea);
		else
			text = &(data->map_i->we);
	}
	return (text);
}

static void	setup_dda2(t_data *data)
{
	if (data->ray_i->raydirx == 0)
		data->ray_i->deltadistx = 1e30;
	else
		data->ray_i->deltadistx = fabs(1 / data->ray_i->raydirx);
	if (data->ray_i->raydiry == 0)
		data->ray_i->deltadisty = 1e30;
	else
		data->ray_i->deltadisty = fabs(1 / data->ray_i->raydiry);
}

void	setup_dda(t_data *data)
{
	setup_dda2(data);
	if (data->ray_i->raydirx < 0)
	{
		data->ray_i->stepx = -1;
		data->ray_i->sidedistx = (data->ray_i->posx - data->ray_i->mapx)
			* data->ray_i->deltadistx;
	}
	else
	{
		data->ray_i->stepx = 1;
		data->ray_i->sidedistx = (data->ray_i->mapx + 1.0 - data->ray_i->posx)
			* data->ray_i->deltadistx;
	}
	if (data->ray_i->raydiry < 0)
	{
		data->ray_i->stepy = -1;
		data->ray_i->sidedisty = (data->ray_i->posy - data->ray_i->mapy)
			* data->ray_i->deltadisty;
	}
	else
	{
		data->ray_i->stepy = 1;
		data->ray_i->sidedisty = (data->ray_i->mapy + 1.0 - data->ray_i->posy)
			* data->ray_i->deltadisty;
	}
}

t_texture	*dda(t_data *data)
{
	t_texture	*text;

	text = NULL;
	while (text == NULL)
	{
		if (data->ray_i->sidedistx < data->ray_i->sidedisty)
			text = step_x(data);
		else
			text = step_y(data);
	}
	if (data->ray_i->side == 0)
		data->ray_i->perpwalldist
			= data->ray_i->sidedistx - data->ray_i->deltadistx;
	else
		data->ray_i->perpwalldist
			= (data->ray_i->sidedisty - data->ray_i->deltadisty);
	return (text);
}
