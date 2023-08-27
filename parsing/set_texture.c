/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:38:09 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 02:39:14 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_texture_c(t_data *data, char *buff)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	data->map_i->c1 = gc_malloc(&data->gc, sizeof(int) * 3);
	while (i < 3)
	{
		data->map_i->c1[i] = 0;
		while (buff[j] && buff[j] != ',')
		{
			if (ft_isdigit(buff[j]) == 1)
			{
				data->map_i->c1[i] *= 10;
				data->map_i->c1[i] += (buff[j] - 48);
			}
			j++;
		}
		j++;
		i++;
	}
}

void	set_texture_f(t_data *data, char *buff)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	data->map_i->f1 = gc_malloc(&data->gc, sizeof(int) * 3);
	while (i < 3)
	{
		data->map_i->f1[i] = 0;
		while (buff[j] && buff[j] != ',')
		{
			if (ft_isdigit(buff[j]) == 1)
			{
				data->map_i->f1[i] *= 10;
				data->map_i->f1[i] += (buff[j] - 48);
			}
			j++;
		}
		j++;
		i++;
	}
}

void	set_map_data(t_data *data, char *buff, int info, int fd)
{
	(void)fd;
	if (info == 1)
		data->map_i->no1 = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 2)
		data->map_i->so1 = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 3)
		data->map_i->we1 = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 4)
		data->map_i->ea1 = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 5)
		set_texture_f(data, buff);
	else if (info == 6)
		set_texture_c(data, buff);
}
