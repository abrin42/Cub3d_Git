/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 00:23:29 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 03:43:11 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_player(t_data *data)
{
	int	y;
	int	x;
	int	player;

	player = 0;
	y = 0;
	while (y < data->y_map - 1)
	{
		x = 0;
		while (data->map_i->map[y][x] && x < data->x_map)
		{
			if (data->map_i->map[y][x] && is_players
				(data->map_i->map[y][x]) == 1)
			{
				data->map_i->map[y][x] = '0';
				player++;
			}
			x++;
		}
		y++;
	}
	return (player);
}

int	check_texture(t_data *data)
{
	int	error;

	error = 0;
	if (!data->map_i->no1)
		error++;
	if (!data->map_i->so1)
		error++;
	if (!data->map_i->we1)
		error++;
	if (!data->map_i->ea1)
		error++;
	if (!data->map_i->f1)
		error++;
	if (!data->map_i->c1)
		error++;
	if (error != 0)
	{
		printf("Error : In the file map.cub not all ");
		printf("textures are defined (example \"NO ");
		printf("./path_to_the_north_texture\", same ");
		printf("with SO, WE, EA and \"F 220,100,\" same with C) \n");
		return (1);
	}
	return (0);
}

int	check_name(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		i++;
	}
	if (argv[i - 4] == '.' && argv[i - 3] == 'c'
		&& argv[i - 2] == 'u' && argv[i - 1] == 'b')
	{
		return (0);
	}
	printf("Error : Only .cub files are accepted by the program\n");
	return (1);
}

int	check_xpm(t_data *data)
{
	int	error;

	error = 0;
	if (ft_strnrchr(data->map_i->no1, ".xpm") != 1)
		error++;
	if (ft_strnrchr(data->map_i->so1, ".xpm") != 1)
		error++;
	if (ft_strnrchr(data->map_i->ea1, ".xpm") != 1)
		error++;
	if (ft_strnrchr(data->map_i->we1, ".xpm") != 1)
		error++;
	if (error != 0)
	{
		printf("Error : Textures must be in .xpm format\n");
		return (1);
	}
	return (0);
}

int	check_error(t_data *data, char *argv)
{
	if (check_border_map(data) == 1)
		return (1);
	if (check_texture(data) == 1)
		return (1);
	if (check_name(argv) == 1)
		return (1);
	if (check_xpm(data) == 1)
		return (1);
	check_right(data);
	if (data->map_i->map_error != 0)
	{
		printf("Error : the map is not closed\n");
		return (1);
	}
	return (0);
}
