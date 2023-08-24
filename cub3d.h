/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:35:25 by abrin             #+#    #+#             */
/*   Updated: 2023/08/25 00:48:37 by abrin            ###   ########.fr       */
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
# include <math.h>
# include "gc/gc.h"
# include "minilibx-linux/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_map
{
	char	**map;
	char	**copy_map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		*F;
	int		*C;
	int		x_wall;//start suprimer pas usse
	int		y_wall; //start suprimer pas usse
	int		map_error;
	int			cell_color;
	int			floor_color;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char		*img_addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_mlx;

typedef struct s_ray
{
	int		screen_w;
	int		screen_h;
	double	posX;
	double	posY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	double	dirX;
	double	dirY;
	double	rayDirX;
	double	rayDirY;
	double	planeX;
	double	planeY;
	double	cameraX;
	double	time;
	double	oldTime;
}	t_ray;

typedef struct s_data
{
	char *path_map;
	int x_map;
	int y_map;

	t_gcan	gc;
	t_ray	*ray_i;
	t_mlx *mlx_i;
	t_map *map_i;
}	t_data;



/***********MAIN************************************/


/***********UTILS***********************************/

int			ft_strlen(char *str);
int			ft_strchr(char *string);
int			ft_strncmp(char *str1, char *str2, int length);
//char		*ft_strnstr(char *big, char *lit, size_t len);
char		*ft_strstr(char *big, char *lit);
int			ft_isdigit(int c);


char		*ft_strdup(t_data *data, const char *s);
char		*ft_strdup_special(t_data *data ,const char *s);

char		*get_next_line(int fd);

/*********PARSING***********************************/
void		get_map(t_data *data, char *argv);
int			check_border_map(t_data *data);
int			check_player(t_data *data);
int			check_error(t_data *data, char *argv);


void	check_right(t_data *data);
void	check_down(t_data *data);
void	check_left(t_data *data);
void	check_up(t_data *data);
/*********RAYTRACING***********************************/
int	display(void *param);



#endif
