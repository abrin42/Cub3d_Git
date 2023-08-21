/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 03:00:15 by abrin             #+#    #+#             */
/*   Updated: 2023/08/21 09:10:54 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *data)
{
	data->x_malloc_map = 0;
	data->y_mallocc_map = 0;
	data->map_info = malloc(sizeof(t_map));
}

int main(int argc, char **argv)
{
	t_data data;

	init(&data);
	get_map(&data, argv[1]);
	for (size_t i = 0; i < 9; i++)
	{
		printf("%s\n", data.map_info->map[i]);
	}
}
