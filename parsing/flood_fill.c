/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:29:35 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 02:30:50 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_right(t_data *data)
{
	check_exit(data);
	if (data->map_i->copy_map[data->map_i->x_wall + 1]
		[data->map_i->y_wall] == '0'
		|| data->map_i->copy_map[data->map_i->x_wall + 1]
		[data->map_i->y_wall] == ' ')
	{
		data->map_i->x_wall++;
		data->map_i->copy_map[data->map_i->x_wall][data->map_i->y_wall] = '2';
		check_right(data);
		data->map_i->x_wall--;
	}
	check_down(data);
}

void	check_down(t_data *data)
{
	check_exit(data);
	if (data->map_i->copy_map[data->map_i->x_wall]
		[data->map_i->y_wall + 1] == '0'
		|| data->map_i->copy_map[data->map_i->x_wall]
		[data->map_i->y_wall + 1] == ' ')
	{
		data->map_i->y_wall++;
		data->map_i->copy_map[data->map_i->x_wall]
		[data->map_i->y_wall] = '2';
		check_right(data);
		data->map_i->y_wall--;
	}
	check_left(data);
}

void	check_left(t_data *data)
{
	check_exit(data);
	if (data->map_i->copy_map[data->map_i->x_wall - 1]
		[data->map_i->y_wall] == '0'
		|| data->map_i->copy_map[data->map_i->x_wall - 1]
		[data->map_i->y_wall] == ' ')
	{
		data->map_i->x_wall--;
		data->map_i->copy_map[data->map_i->x_wall]
		[data->map_i->y_wall] = '2';
		check_right(data);
		data->map_i->x_wall++;
	}
	check_up(data);
}

void	check_up(t_data *data)
{
	check_exit(data);
	if (data->map_i->copy_map[data->map_i->x_wall]
		[data->map_i->y_wall - 1] == '0'
		|| data->map_i->copy_map[data->map_i->x_wall]
		[data->map_i->y_wall - 1] == ' ')
	{
		data->map_i->y_wall--;
		data->map_i->copy_map[data->map_i->x_wall]
		[data->map_i->y_wall] = '2';
		check_right(data);
		data->map_i->y_wall++;
	}
	check_exit(data);
}
