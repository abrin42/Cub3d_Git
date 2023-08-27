/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:35:25 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 03:22:53 by abrin            ###   ########.fr       */
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
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_map
{
	char		**map;
	char		**copy_map;
	char		*no1;
	char		*so1;
	char		*we1;
	char		*ea1;
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
	int			*f1;
	int			*c1;
	int			x_wall;
	int			y_wall;
	int			map_error;
	int			cell_color;
	int			floor_color;
	int			trace;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*img_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_ray
{
	int		screen_w;
	int		screen_h;
	double	posx;
	double	posy;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	dirx;
	double	diry;
	double	raydirx;
	double	raydiry;
	double	planex;
	double	planey;
	double	camerax;
	double	time;
	double	oldtime;
}	t_ray;

typedef struct s_data
{
	char	*path_map;
	int		x_map;
	int		y_map;
	int		line_height_spe;

	t_gcan	gc;
	t_ray	*ray_i;
	t_mlx	*mlx_i;
	t_map	*map_i;
}	t_data;

/***********INIT***********************************/

void		init(t_data *data);
void		init_ray(t_data *data);

/***********UTILS***********************************/

int			ft_strlen(char *str);
int			ft_strchr(char *string);
int			ft_strncmp(char *str1, char *str2, int length);
char		*ft_strstr(char *big, char *lit);
int			ft_isdigit(int c);
int			ft_strnrchr(char *s, char *c);
char		*ft_strdup(t_data *data, const char *s);
char		*ft_strdup_special(t_data *data, const char *s);
char		*get_next_line(t_data *data, int fd);

/*********PARSING***********************************/

void		get_map(t_data *data, char *argv);
int			check_border_map(t_data *data);
int			check_player(t_data *data);
int			check_error(t_data *data, char *argv);
void		setup_texture(t_data *data);
void		check_right(t_data *data);
void		check_down(t_data *data);
void		check_left(t_data *data);
void		check_up(t_data *data);
void		check_exit(t_data *data);
void		open_malloc_map(t_data *data);
void		malloc_map(t_data *data, int fd, char *buff);
void		copy_other_line_map(t_data *data, int fd, char *buff);
void		copy_first_line_map(t_data *data, char *buff, int fd);
void		set_map_data(t_data *data, char *buff, int info, int fd);
void		set_texture_f(t_data *data, char *buff);
void		set_texture_c(t_data *data, char *buff);
void		check_character(t_data *data, char pos, int x, int y);
int			is_players(char c);

/*********RAYTRACING***********************************/

int			display(t_data *data);
void		draw_map2D(t_data *data);
void		rotate_player(t_data *data, double angle);
void		setup_dda(t_data *data);
void		setup_texture2(t_data *data);
void		setup_texture(t_data *data);
void		set(int line_height, int *draw_start, int *draw_end, t_data *data);
int			get_pix_color(t_texture *text, int x, int y);
void		setup_texture2(t_data *data);
t_texture	*dda(t_data *data);
void		setup_dda(t_data *data);

/*********KEY MLX***********************************/

void		key_w(t_data *data);
void		key_a(t_data *data);
void		key_d(t_data *data);
void		key_s(t_data *data);
int			handle_input(int key, t_data *data);

#endif
