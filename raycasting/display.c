#include "../cub3d.h"

void	draw_player(t_data *data)
{
	//(void)data;
	printf("ICI X : %f et Y : %f\n", data->ray_i->posX, data->ray_i->posY);
	mlx_pixel_put(data->mlx_i->mlx, data->mlx_i->mlx_win, data->ray_i->posX * 32, data->ray_i->posY * 32, 0xFF0000);
}

void	my_mlx_put(t_data *data, int y, int x)
{
	mlx_put_image_to_window(data->mlx_i->mlx, data->mlx_i->mlx_win, data->mlx_i->img, 32 * x, 32 * y);
}

void	draw_map2D(t_data *data)
{
	int	x;
	int	y;
	int	w;
	int	h;

	x = 0;
	while (x < data->x_map)
	{
		y = 0;
		while (y < data->y_map)
		{
			if (data->map_i->map[y][x] == '1')
				data->mlx_i->img = mlx_xpm_file_to_image (data->mlx_i->mlx, "img/white.xpm", &w, &h);
			else if (data->map_i->map[y][x] == '0')
				data->mlx_i->img = mlx_xpm_file_to_image (data->mlx_i->mlx, "img/grey.xpm", &w, &h);
			my_mlx_put(data, y, x);
			y++;
		}
		x++;
	}

}

static void	setup_dda2(t_data *data)
{
	if (data->ray_i->rayDirX == 0)
		data->ray_i->deltaDistX = 1e30;
	else
		data->ray_i->deltaDistX = fabs(1 / data->ray_i->rayDirX);
	if (data->ray_i->rayDirY == 0)
		data->ray_i->deltaDistY = 1e30;
	else
		data->ray_i->deltaDistY = fabs(1 / data->ray_i->rayDirY);
}

void	setup_dda(t_data *data)
{
	setup_dda2(data);
	if (data->ray_i->rayDirX < 0)
	{
		data->ray_i->stepX = -1;
		data->ray_i->sideDistX = (data->ray_i->posX - data->ray_i->mapX) * data->ray_i->deltaDistX;
	}
	else
	{
		data->ray_i->stepX = 1;
		data->ray_i->sideDistX = (data->ray_i->mapX + 1.0 - data->ray_i->posX) * data->ray_i->deltaDistX;
	}
	if (data->ray_i->rayDirY < 0)
	{
		data->ray_i->stepY = -1;
		data->ray_i->sideDistY = (data->ray_i->posY - data->ray_i->mapY) * data->ray_i->deltaDistY;
	}
	else
	{
		data->ray_i->stepY = 1;
		data->ray_i->sideDistY = (data->ray_i->mapY + 1.0 - data->ray_i->posY) * data->ray_i->deltaDistY;
	}
}

t_texture	*dda(t_data *data)
{
	t_texture	*text;

	text = NULL;
	while (text == NULL)
	{
		if (data->ray_i->sideDistX < data->ray_i->sideDistY)
		{
			data->ray_i->sideDistX += data->ray_i->deltaDistX;
			data->ray_i->mapX += data->ray_i->stepX;
			data->ray_i->side = 0;
		}
		else
		{
			data->ray_i->sideDistY += data->ray_i->deltaDistY;
			data->ray_i->mapY += data->ray_i->stepY;
			data->ray_i->side = 1;
		}
	}
	if (data->ray_i->side == 0)
		data->ray_i->perpWallDist = data->ray_i->sideDistX - data->ray_i->deltaDistX;
	else
		data->ray_i->perpWallDist = (data->ray_i->sideDistY - data->ray_i->deltaDistY);
	return (text);
}

void	set(int line_height, int *draw_start, int *draw_end, t_data *data)
{
	(*draw_start) = (-line_height / 2) + (data->ray_i->screen_h / 2);
	if ((*draw_start) < 0)
		(*draw_start) = 0;
	if ((*draw_start) >= data->ray_i->screen_h)
		(*draw_start) = data->ray_i->screen_h - 1;
	(*draw_end) = (line_height / 2) + (data->ray_i->screen_h / 2);
	if ((*draw_end) >= data->ray_i->screen_h)
		(*draw_end) = data->ray_i->screen_h - 1;
}

int	get_pix_color(t_texture *text, int x, int y)
{
	return (*(int *)(text->addr \
			+ (4 * text->width * y) \
			+ (4 * x)));
}

void	img_pix_put(int x, int y, int color, t_data *data)
{
	char	*dst;

	dst = data->mlx_i->img_addr + \
		(y * data->mlx_i->line_len + x * (data->mlx_i->bpp / 8));
	*(unsigned int *)dst = color;
}

void	vertical_line(int x, int line_height, t_texture *text, int textX, t_data *data)
{
	int		y;
	int		draw_start;
	int		draw_end;
	double	step;
	double	textY;

	set(line_height, &draw_start, &draw_end, data);
	y = 0;
	step = ((double)(text->height) / (double)(draw_end - draw_start));
	while (y < draw_start)
		img_pix_put(x, y++, data->map_i->cell_color, data);
	textY = 0.0;
	while (y < draw_end)
	{
		img_pix_put(x, y++, get_pix_color(text, textX, (int)textY), data);
		textY += step;
	}
	while (y < data->ray_i->screen_h)
		img_pix_put(x, y++,  data->map_i->floor_color, data);
}

static void render_line(t_data *data, int x)
{
	double		wallX;
	t_texture	*text;
	int			textX;

	text = dda(data);
	if (data->ray_i->side == 0)
		wallX = data->ray_i->posY + (data->ray_i->perpWallDist * data->ray_i->rayDirY);
	else
		wallX = data->ray_i->posX + (data->ray_i->perpWallDist * data->ray_i->rayDirX);
	wallX -= floor(wallX);
	textX = (int)(wallX * (double)text->width);
	if (data->ray_i->side == 0 && data->ray_i->rayDirX > 0)
		textX = text->width - textX - 1;
	if (data->ray_i->side == 1 && data->ray_i->rayDirY < 0)
		textX = text->width - textX - 1;
	vertical_line(x, (int)(data->ray_i->screen_h / data->ray_i->perpWallDist), text, textX, data);
}

int	display(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->ray_i->screen_w)
	{
		data->ray_i->cameraX = (2 * (x / (double)data->ray_i->screen_w)) - 1;
		data->ray_i->rayDirX = data->ray_i->dirX + data->ray_i->planeX * data->ray_i->cameraX;
		data->ray_i->rayDirY = data->ray_i->dirY + data->ray_i->planeY * data->ray_i->cameraX;
		data->ray_i->mapX = (int)data->ray_i->posX;
		data->ray_i->mapY = (int)data->ray_i->posY;
		setup_dda(data);
		render_line(data, x++);
		x++;
	}
	mlx_put_image_to_window(data->mlx_i->mlx, data->mlx_i->mlx_win, data->mlx_i->img, 0, 0);
	return (0);
}

void	setup_texture2(t_data *data)
{
	data->map_i->no.img = mlx_xpm_file_to_image(data->mlx_i->mlx, data->map_i->NO, &(data->map_i->no.width), &(data->map_i->no.height));
	data->map_i->no.addr = mlx_get_data_addr(data->map_i->no.img, &(data->map_i->no.bpp), &(data->map_i->no.line_len), &(data->map_i->no.endian));
	data->map_i->so.img = mlx_xpm_file_to_image(data->mlx_i->mlx, data->map_i->SO, &(data->map_i->so.width), &(data->map_i->so.height));
	data->map_i->so.addr = mlx_get_data_addr(data->map_i->so.img, &(data->map_i->so.bpp), &(data->map_i->so.line_len), &(data->map_i->so.endian));
	data->map_i->we.img = mlx_xpm_file_to_image(data->mlx_i->mlx, data->map_i->WE, &(data->map_i->we.width), &(data->map_i->we.height));
	data->map_i->we.addr = mlx_get_data_addr(data->map_i->we.img, &(data->map_i->we.bpp), &(data->map_i->we.line_len), &(data->map_i->we.endian));
	data->map_i->ea.img = mlx_xpm_file_to_image(data->mlx_i->mlx, data->map_i->EA, &(data->map_i->ea.width), &(data->map_i->ea.height));
	data->map_i->ea.addr = mlx_get_data_addr(data->map_i->ea.img, &(data->map_i->ea.bpp), &(data->map_i->ea.line_len), &(data->map_i->ea.endian));
}

void	setup_texture(t_data *data)
{
	setup_texture2(data);
}
