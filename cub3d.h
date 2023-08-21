/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:35:25 by abrin             #+#    #+#             */
/*   Updated: 2023/08/21 08:01:07 by abrin            ###   ########.fr       */
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
# include "gc/gc.h"
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_map
{
	char **map;
}	t_map;

typedef struct s_data
{
	char *path_map;
	int x_malloc_map;
	int y_mallocc_map;


	t_map *map_info;
}	t_data;



/***********MAIN************************************/


/***********UTILS***********************************/

size_t		ft_strlen(char *str);
int			ft_strchr(char *string);
int			ft_strncmp(char *str1, char *str2, int length);
char		*ft_strnstr(char *big, char *lit, size_t len);
char		*ft_strdup(const char *s);



char		*get_next_line(int fd);

/*********PARSING***********************************/
void		get_map(t_data *data, char *argv);


#endif
