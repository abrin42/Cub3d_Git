/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 03:16:29 by abrin             #+#    #+#             */
/*   Updated: 2023/08/26 02:45:19 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_texture_c(t_data *data, char *buff)
{
	int i;
	int j;

	j = 0;
	i = 0;
	data->map_i->C = gc_malloc(&data->gc, sizeof(int) * 3);
	while(i < 3)
	{
		data->map_i->C[i] = 0;
		while(buff[j] && buff[j] != ',')
		{
			if (ft_isdigit(buff[j]) == 1)
			{
				data->map_i->C[i] *= 10;
				data->map_i->C[i] += (buff[j] - 48);
			}
			j++;
		}
		j++;
		i++;
	}
}

void	set_texture_f(t_data *data, char *buff)
{
	int i;
	int j;

	j = 0;
	i = 0;
	data->map_i->F = gc_malloc(&data->gc, sizeof(int) * 3);
	while(i < 3)
	{
		data->map_i->F[i] = 0;
		while(buff[j] && buff[j] != ',')
		{
			if (ft_isdigit(buff[j]) == 1)
			{
				data->map_i->F[i] *= 10;
				data->map_i->F[i] += (buff[j] - 48);
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
		data->map_i->NO = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 2)
		data->map_i->SO = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 3)
		data->map_i->WE = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 4)
		data->map_i->EA = ft_strdup(data, ft_strstr(buff, "./"));
	else if (info == 5)
		set_texture_f(data, buff);
	else if (info == 6)
		set_texture_c(data, buff);
}

void	malloc_map(t_data *data, int fd, char *buff)
{
	int y;

	y = 0;
	while (buff != NULL)
	{
		buff = get_next_line(fd);
		/*if (!buff[0])
		{
			printf("this break\n");
			break;
		}
		//printf("%s\n",buff);*/
		if (ft_strstr(buff, "1") != 0)
			data->y_map++;
		if (ft_strlen(buff) > data->x_map)
			data->x_map = ft_strlen(buff);
		free(buff);
	}
	data->map_i->map = gc_malloc(&data->gc ,sizeof(char *) * data->y_map + 1);
	while (y < data->y_map)
	{
		data->map_i->map[y] =gc_malloc(&data->gc, sizeof(char) * data->x_map + 1);
		y++;
	}
	printf("y malloc %d, x malloc%d\n\n",data->y_map,data->x_map);
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
		//printf("\nbuff[%d]*%s*\n",i,buff);
		if (ft_strstr(buff, "1111") != 0)
		{
			//printf("laaaa\n");
			data->y_map++;
			data->x_map = ft_strlen(buff);
			malloc_map(data, fd, buff);
			if (data->map_i->trace != 0)
			{
				free(buff);
				break;
			}
		}
		free(buff);
		i++;
	}
	//write(1,"here**\n",7);
	//printf("y malloc %d, x malloc%d\n\n",data->y_map,data->x_map);
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
	int y_2;

	y_2 = 0;
	y = 1;
	while (y < data->y_map + y_2)
	{
		x = 0;
		buff = get_next_line(fd);
		//printf("buff fee%s\n",buff);
		if (!buff)
		{
			printf("break here\n");
			break;
		}
		while (buff[x] && x < data->x_map)
		{
			check_character(data, buff[x], x, y);
			data->map_i->map[y][x] = buff[x];
			x++;
		}
		data->map_i->map[y][x] = '\0';
			//printf("%s-\n", data->map_i->map[y]);
		if (ft_strstr(buff, "1") != 0)
			y++;
		else
		{
			y_2++;
		}
		free(buff);
	}
	printf("buff fee%s\n",buff);
	//data->map_i->trace++;
}

void	copy_first_line_map(t_data *data, char *buff, int fd)
{
	int	x;
	int y;

	y = 0;
	x = 0;
	//open_malloc_map(data);
	while (buff[x] && x < data->x_map)
	{
		data->map_i->map[y][x] = buff[x];
		x++;
	}
	//printf("%s-\n", data->map_i->map[0]);
	data->map_i->map[y][x] = '\0';
	data->map_i->trace++;
	copy_other_line_map(data, fd , buff);



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

void transfert_map(t_data *data,int fd)
{
	char	*buff;
	int i;

	i = 0;
	while (i == 0 || buff != NULL)
	{
		buff = get_next_line(fd);
		if(!buff)
		{
			free(buff);
			break;
		}
		check_info(data, buff, fd);
		if (data->map_i->trace != 0)
		{
			free(buff);
			break;
		}
		printf("next step \n");
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
