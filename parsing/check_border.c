/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 03:36:14 by abrin             #+#    #+#             */
/*   Updated: 2023/08/22 08:28:53 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	search_wall(t_data *data) // a suprimer et remplacer par la pos du joueur data->map
{
	int	x;
	int y;
	int trace;

	trace = 0;
	y = 1;
	while (y < data->y_map)
	{
		x = 1;
		while (x < data->x_map + 2)
		{
			if (data->map_i->copy_map[y][x] == '0')
			{
				trace++;
				break ;
			}
			x++;
		}
		if (trace != 0)
			break ;
		y++;
	}
	data->map_i->x_wall = x;
	data->map_i->y_wall = y;
	data->map_i->copy_map[y][x] = '+';
	return(x);

}

void	malloc_copy_map(t_data *data)
{
	int	y;

	y = 0;
	data->map_i->copy_map = gc_malloc(&data->gc ,sizeof(char *) * data->y_map + 3);
	while (y < data->y_map)
	{
		data->map_i->copy_map[y] =gc_malloc(&data->gc, sizeof(char) * data->x_map + 2);
		y++;
	}
}

void	copy_map(t_data *data)
{
	int y;
	int x;

	x = 0;
	y = 0;
	while (x < data->x_map + 2)
	{
		data->map_i->copy_map[y][x] = '4';
		x++;
	}
	while (y < data->y_map)
	{
		data->map_i->copy_map[y + 1] = ft_strdup_special(data->map_i->map[y]);
		y++;
	}
	data->map_i->copy_map[y + 1] = ft_strdup(data->map_i->copy_map[0]);
}

void	check_exit(t_data *data)
{
	if(data->map_i->copy_map[data->map_i->y_wall][data->map_i->x_wall + 1] == '4')
		data->map_i->map_error++;
	if(data->map_i->copy_map[data->map_i->y_wall][data->map_i->x_wall - 1] == '4')
		data->map_i->map_error++;
	if(data->map_i->copy_map[data->map_i->y_wall + 1][data->map_i->x_wall] == '4')
		data->map_i->map_error++;
	if(data->map_i->copy_map[data->map_i->y_wall - 1][data->map_i->x_wall] == '4')
		data->map_i->map_error++;
}

void	check_right(t_data *data)
{
	check_exit(data);
	if (data->map_i->copy_map[data->map_i->y_wall][data->map_i->x_wall + 1] == '0'
		|| data->map_i->copy_map[data->map_i->y_wall][data->map_i->x_wall + 1] == ' ')
	{
		data->map_i->x_wall++;
		data->map_i->copy_map[data->map_i->y_wall][data->map_i->x_wall] = '2';
		check_right(data);
		data->map_i->x_wall--;
	}
	check_down(data);
}

void	check_down(t_data *data)
{
	check_exit(data);
	if (data->map_i->copy_map[data->map_i->y_wall + 1][data->map_i->x_wall] == '0'
		|| data->map_i->copy_map[data->map_i->y_wall + 1][data->map_i->x_wall] == ' ')
	{
		data->map_i->y_wall++;
		data->map_i->copy_map[data->map_i->y_wall][data->map_i->x_wall] = '2';
		check_right(data);
		data->map_i->y_wall--;
	}
	check_left(data);
}

void	check_left(t_data *data)
{
	check_exit(data);
	if (data->map_i->copy_map[data->map_i->y_wall][data->map_i->x_wall - 1] == '0'
		|| data->map_i->copy_map[data->map_i->y_wall][data->map_i->x_wall - 1] == ' ')
	{
		data->map_i->x_wall--;
		data->map_i->copy_map[data->map_i->y_wall][data->map_i->x_wall] = '2';
		check_right(data);
		data->map_i->x_wall++;
	}
	check_up(data);
}

void	check_up(t_data *data)
{
	check_exit(data);
	if (data->map_i->copy_map[data->map_i->y_wall - 1][data->map_i->x_wall] == '0'
		|| data->map_i->copy_map[data->map_i->y_wall - 1][data->map_i->x_wall] == ' ')
	{
		data->map_i->y_wall--;
		data->map_i->copy_map[data->map_i->y_wall][data->map_i->x_wall] = '2';
		check_right(data);
		data->map_i->y_wall++;
	}
	check_exit(data);
}

int	check_border_map(t_data *data)
{

	malloc_copy_map(data);
	copy_map(data);
	data->map_i->x_wall = data->ray_i->posX;
	data->map_i->y_wall = data->ray_i->posY;
	check_right(data);
	if (data->map_i->map_error != 0)
		printf("\n\nmap non valide\n**********************");

	/*printf("\n\n-------------copy map------------\n");
	for (size_t i = 0; (int)i < data->y_map + 2; i++)
	{
		printf("\n%s", data->map_i->copy_map[i]);
	}*/
	return(0);
}
