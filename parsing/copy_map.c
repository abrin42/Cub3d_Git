/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:34:55 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 02:37:08 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	copy_other_line_map(t_data *data, int fd, char *buff)
{
	int	x;
	int	y;
	int	y_2;

	y_2 = 0;
	y = 1;
	while (y < data->y_map + y_2)
	{
		x = 0;
		buff = get_next_line(data, fd);
		if (!buff)
			break ;
		while (buff[x] && x < data->x_map)
		{
			check_character(data, buff[x], x, y);
			data->map_i->map[y][x] = buff[x];
			x++;
		}
		data->map_i->map[y][x] = '\0';
		if (ft_strstr(buff, "1") != 0)
			y++;
		else
			y_2++;
		free(buff);
	}
}

void	copy_first_line_map(t_data *data, char *buff, int fd)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (buff[x] && x < data->x_map)
	{
		data->map_i->map[y][x] = buff[x];
		x++;
	}
	data->map_i->map[y][x] = '\0';
	data->map_i->trace++;
	copy_other_line_map(data, fd, buff);
}
