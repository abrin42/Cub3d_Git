
#include "../cub3d.h"

int	is_players(char c)
{
	if(c == 'N')
		return(1);
	else if (c == 'S')
		return(1);
	else if (c == 'E')
		return(1);
	else if (c == 'W')
		return(1);
	return(0);
}

int	check_player(t_data *data)
{
	int y;
	int x;
	int player;

	player = 0;
	y = 0;
	while (y < data->y_map - 1)
	{
		x = 0;
		while (x < data->x_map)
		{
			if (is_players(data->map_i->map[y][x]) == 1)
				player++;
			x++;
		}
		y++;
	}
	return(player);

}
int	check_texture(t_data *data)
{
	int error;

	error = 0;
	if (!data->map_i->NO)
		error++;
	if (!data->map_i->SO)
		error++;
	if (!data->map_i->WE)
		error++;
	if (!data->map_i->EA)
		error++;
	if (!data->map_i->F)
		error++;
	if (!data->map_i->C)
		error++;
	if (error != 0)
	{
		printf("Error : In the file map.cub not all ");
		printf("textures are defined (example \"NO ");
		printf("./path_to_the_north_texture\", same ");
		printf("with SO, WE, EA and \"F 220,100,\" same with C) \n");
		return(1);
	}
	return (0);
}
int	check_name(char *argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		i++;
	}
	if (argv[i - 4] != '.' && argv[i - 3] != 'c'
		&& argv[i - 2] != 'u' && argv[i - 1] != 'b')
	{
		printf("Error : Only .cub files are accepted by the program\n");
		return (1);
	}
	return (0);

}

int check_xpm(t_data *data)
{
	int error;

	error = 0;
	if (ft_strnrchr(data->map_i->NO, ".xpm") != 1)
		error++;
	if (ft_strnrchr(data->map_i->SO, ".xpm") != 1)
		error++;
	if (ft_strnrchr(data->map_i->EA, ".xpm") != 1)
		error++;
	if (ft_strnrchr(data->map_i->WE, ".xpm") != 1)
		error++;
	if (error != 0)
	{
		printf("Error : Textures must be in .xpm format\n");
		return(1);
	}
	return (0);
}

int check_error(t_data *data, char *argv)
{
	if (check_border_map(data) == 1)
		return(1);
	if (check_texture(data) == 1)
		return(1);
	if (check_name(argv) == 1)
		return(1);
	if(check_xpm(data) == 1)
		return(1);
	return (0);
}
