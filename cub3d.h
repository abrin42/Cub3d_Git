/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:35:25 by abrin             #+#    #+#             */
/*   Updated: 2023/08/22 00:24:19 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "gc/gc.h"
# include "minilibx-linux/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_map
{
	char **map;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
}	t_mlx;

typedef struct s_ray
{
}	t_ray;

typedef struct s_data
{
	char *path_map;
	int x_malloc_map;
	int y_mallocc_map;

	t_gcan	gc;
	t_ray	*ray_i;
	t_mlx *mlx_i;
	t_map *map_info;
}	t_data;



/***********MAIN************************************/


/***********UTILS***********************************/

int		ft_strlen(char *str);
int			ft_strchr(char *string);
int			ft_strncmp(char *str1, char *str2, int length);
char		*ft_strnstr(char *big, char *lit, size_t len);
char		*ft_strdup(const char *s);
char		*get_next_line(int fd);

/*********PARSING***********************************/
void		get_map(t_data *data, char *argv);


#endif
