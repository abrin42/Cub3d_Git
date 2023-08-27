/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 03:16:29 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 02:39:00 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_character(t_data *data, char pos, int x, int y)
{
	if (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'W')
	{
		if (pos == 'S')
			rotate_player(data, 3.141592);
		else if (pos == 'E')
			rotate_player(data, -1.57);
		else if (pos == 'W')
			rotate_player(data, 1.57);
		data->ray_i->posx = y;
		data->ray_i->posy = x;
	}
}

void	check_info(t_data *data, char *buff, int fd)
{
	if (ft_strncmp(buff, "NO", 2) == 0)
		set_map_data(data, buff, 1, fd);
	else if (ft_strncmp(buff, "SO", 2) == 0)
		set_map_data(data, buff, 2, fd);
	else if (ft_strncmp(buff, "WE", 2) == 0)
		set_map_data(data, buff, 3, fd);
	else if (ft_strncmp(buff, "EA", 2) == 0)
		set_map_data(data, buff, 4, fd);
	else if (ft_strncmp(buff, "F", 1) == 0)
		set_map_data(data, buff, 5, fd);
	else if (ft_strncmp(buff, "C", 1) == 0)
		set_map_data(data, buff, 6, fd);
	else if (ft_strstr(buff, "1111") != 0)
		copy_first_line_map(data, buff, fd);
}

void	transfert_map(t_data *data, int fd)
{
	char	*buff;
	int		i;

	i = 0;
	while (i == 0 || buff != NULL)
	{
		buff = get_next_line(data, fd);
		if (!buff)
		{
			free(buff);
			break ;
		}
		check_info(data, buff, fd);
		if (data->map_i->trace != 0)
		{
			free(buff);
			break ;
		}
		i++;
		free(buff);
	}
}

void	get_map(t_data *data, char *argv)
{
	int	fd;

	data->path_map = ft_strdup(data, argv);
	open_malloc_map(data);
	fd = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		printf("Error : to run the program use a map.cub\n");
		exit(0);
	}
	transfert_map(data, fd);
	close(fd);
}
