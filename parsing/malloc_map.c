/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:34:40 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 02:36:23 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	malloc_map(t_data *data, int fd, char *buff)
{
	int	y;

	y = 0;
	while (buff != NULL)
	{
		buff = get_next_line(data, fd);
		if (ft_strstr(buff, "1") != 0)
			data->y_map++;
		if (ft_strlen(buff) > data->x_map)
			data->x_map = ft_strlen(buff);
		free(buff);
	}
	data->map_i->map = gc_malloc(&data->gc, sizeof(char *) * data->y_map + 1);
	while (y < data->y_map)
	{
		data->map_i->map[y] = gc_malloc(&data->gc,
				sizeof(char) * data->x_map + 1);
		y++;
	}
}

void	open_malloc_map(t_data *data)
{
	char	*buff;
	int		i;
	int		fd;

	i = 0;
	fd = open(data->path_map, O_RDONLY);
	while (i == 0 || buff != NULL)
	{
		buff = get_next_line(data, fd);
		if (ft_strstr(buff, "1111") != 0)
		{
			data->y_map++;
			data->x_map = ft_strlen(buff);
			malloc_map(data, fd, buff);
			if (data->map_i->trace != 0)
			{
				free(buff);
				break ;
			}
		}
		free(buff);
		i++;
	}
	close(fd);
}
