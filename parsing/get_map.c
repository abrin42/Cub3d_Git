/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 03:16:29 by abrin             #+#    #+#             */
/*   Updated: 2023/08/22 07:51:22 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
/*
void	set_texture(t_data *data, char *buff)
{

}*/

void	set_map_data(t_data *data, char *buff, int info, int fd)
{
	(void)fd;
	if (info == 1)
		data->map_info->NO = ft_strdup(ft_strstr(buff, "./"));
	else if (info == 2)
		data->map_info->SO = ft_strdup(ft_strstr(buff, "./"));
	else if (info == 3)
		data->map_info->WE = ft_strdup(ft_strstr(buff, "./"));
	else if (info == 4)
		data->map_info->EA = ft_strdup(ft_strstr(buff, "./"));
	/*else if (info == 5)
		//
	else if (info == 6)*/
		//

	/*else if (ft_strncmp(buff, "F", 2))
		set_map_data(data, buff, 5, fd);
	else if (ft_strncmp(buff, "C", 2))
		set_map_data(data, buff, 6, fd);*/
}

void	malloc_map(t_data *data, int fd, char *buff)
{
	int y;

	y = 0;
	while (buff != NULL)
	{
		buff = get_next_line(fd);
		if (buff != NULL)
		{
			data->y_mallocc_map++;
			if (ft_strlen(buff) > data->x_malloc_map)
				data->x_malloc_map = ft_strlen(buff);
		}
	}
	data->map_info->map = gc_malloc(&data->gc ,sizeof(char *) * data->y_mallocc_map);
	while (y < data->y_mallocc_map)
	{
		data->map_info->map[y] =gc_malloc(&data->gc, sizeof(char) * data->x_malloc_map + 1);
		//data->map_info->map[y][data->y_mallocc_map] = '\0';
		y++;
	}
}

void	open_malloc_map(t_data *data)
{
	char	*buff;
	int i;
	int	fd;

	i = 0;
	fd = open(data->path_map , O_RDONLY);
	while (i == 0 || buff != NULL)
	{
		buff = get_next_line(fd);
		if (ft_strstr(buff, "1111") != 0)
		{
			data->y_mallocc_map++;
			data->x_malloc_map = ft_strlen(buff);
			malloc_map(data, fd, buff);
		}
		i++;
	}
	close(fd);
}

void	check_character(t_data *data, char pos, int x, int y)
{
	if (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'O')
	{
		data->ray_i->posX = x;
		data->ray_i->posY = y;
	}
}

void	copy_other_line_map(t_data *data, int fd, char *buff)
{
	int x;
	int y;

	y = 1;
	while (y < data->y_mallocc_map)
	{
		x = 0;
		buff = get_next_line(fd);
		if (!buff)
			break;
		while (buff[x] && x < data->x_malloc_map)
		{
			check_character(data, buff[x], x, y);
			data->map_info->map[y][x] = buff[x];
			x++;
		}
		data->map_info->map[y][x] = '\0';
		y++;
	}
}

void	copy_first_line_map(t_data *data, char *buff, int fd)
{
	int	x;
	int y;

	y = 0;
	x = 0;
	open_malloc_map(data);
	while (buff[x] && x < data->x_malloc_map)
	{
		data->map_info->map[y][x] = buff[x];
		x++;
	}
	data->map_info->map[y][x] = '\0';
	//printf("map =%s=\n",data->map_info->map[y]);
	copy_other_line_map(data, fd , buff);


}

void	check_info(t_data *data, char *buff, int fd)
{
	//printf("buff =%s=\n", buff);
	/*if (!buff[0])
	{
	//	printf("return\n");
		return ;
	}*/
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

void transfert_map(t_data *data,int fd)
{
	char	*buff;
	int i;

	i = 0;
	while (i == 0 || buff != NULL) //degeu autre moyen ?
	{
		buff = get_next_line(fd);
		check_info(data, buff, fd);
		//free (buff);
	//printf("buff =%s=", buff);
		i++;
	}

}

void	get_map(t_data *data, char *argv)
{
	int	fd;

	fd = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\npour executer le programe utiliser une map");
		exit(0);
	}
	data->path_map = ft_strdup(argv);
	transfert_map(data, fd);
	close(fd);
}
