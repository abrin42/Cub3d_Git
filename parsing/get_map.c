/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 03:16:29 by abrin             #+#    #+#             */
/*   Updated: 2023/08/21 08:56:02 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_map_data(t_data *data, char *buff, int info, int fd)
{

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
		//free(buff); ce free fait la ligne en trop
	}
	data->map_info->map = malloc(sizeof(char *) * data->y_mallocc_map);
	while (y < data->y_mallocc_map)
	{
		data->map_info->map[y] = malloc(sizeof(char) * data->x_malloc_map + 1);
		y++;
	}
	//return(buff);
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
		if (ft_strnstr(buff, "1111", 2048) != 0)
		{
			data->y_mallocc_map++;
			data->x_malloc_map = ft_strlen(buff);
			malloc_map(data, fd, buff);
		}
		//free (buff); //maybe double free
		i++;
	}
	close(fd);
}

void	copy_other_line_map(t_data *data, int fd, char *buff)
{
	int x;
	int y;

	y = 1;
	while (y < data->y_mallocc_map )
	{
		x = 0;
		buff = get_next_line(fd);
		while (buff[x] && x < data->x_malloc_map)
		{
			data->map_info->map[y][x] = buff[x];
			x++;
		}
		y++;
		//printf("buff =%s=", buff);
		//free(buff);
	}
}

void	copy_first_line_map(t_data *data, char *buff, int fd)
{
	int	x;
	int y;

	y = 0;
	x = 0;
	open_malloc_map(data);
	//printf("buff =%s=\n", buff);
	while (buff[x] && x < data->x_malloc_map)
	{
		data->map_info->map[y][x] = buff[x];
		x++;
	}
	//printf("map y =%d=%s=\n\n", y,data->map_info->map[y]);
	copy_other_line_map(data, fd , buff);


}

void	check_info(t_data *data, char *buff, int fd)
{
	/*if (ft_strncmp(buff, "NO", 2))
		set_map_data(data, buff, 1, fd);
	else if (ft_strncmp(buff, "SO", 2))
		set_map_data(data, buff, 2, fd);
	else if (ft_strncmp(buff, "WE", 2))
		set_map_data(data, buff, 3, fd);
	else if (ft_strncmp(buff, "EA", 2))
		set_map_data(data, buff, 4, fd);
	else if (ft_strncmp(buff, "F", 2))
		set_map_data(data, buff, 5, fd);
	else if (ft_strncmp(buff, "C", 2))
		set_map_data(data, buff, 6, fd);*/
	if (ft_strnstr(buff, "1111", 2048) != 0)
	{
		copy_first_line_map(data, buff, fd);
	}
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
