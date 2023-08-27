/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:00:18 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 03:17:34 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	img_pix_put(int x, int y, int color, t_data *data)
{
	char	*dst;

	dst = data->mlx_i->img_addr + \
		(y * data->mlx_i->line_len + x * (data->mlx_i->bpp / 8));
	*(unsigned int *)dst = color;
}

void	vertical_line(int x, t_texture *text, int textX, t_data *data)
{
	int		y;
	int		draw_start;
	int		draw_end;
	double	step;
	double	texty;

	set(data->line_height_spe, &draw_start, &draw_end, data);
	y = 0;
	step = ((double)(text->height) / (double)(draw_end - draw_start));
	while (y < draw_start)
		img_pix_put(x, y++, data->map_i->cell_color, data);
	texty = 0.0;
	while (y < draw_end)
	{
		img_pix_put(x, y++, get_pix_color(text, textX, (int)texty), data);
		texty += step;
	}
	while (y < data->ray_i->screen_h)
		img_pix_put(x, y++, data->map_i->floor_color, data);
}

static void	render_line(t_data *data, int x)
{
	double		wallx;
	t_texture	*text;
	int			textx;

	text = dda(data);
	if (data->ray_i->side == 0)
		wallx = data->ray_i->posy
			+ (data->ray_i->perpwalldist * data->ray_i->raydiry);
	else
		wallx = data->ray_i->posx
			+ (data->ray_i->perpwalldist * data->ray_i->raydirx);
	wallx -= floor(wallx);
	textx = (int)(wallx * (double)text->width);
	if (data->ray_i->side == 0 && data->ray_i->raydirx > 0)
		textx = text->width - textx - 1;
	if (data->ray_i->side == 1 && data->ray_i->raydiry < 0)
		textx = text->width - textx - 1;
	data->line_height_spe = (int)(data->ray_i->screen_h
			/ data->ray_i->perpwalldist);
	vertical_line(x, text, textx, data);
}

int	display(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->ray_i->screen_w)
	{
		data->ray_i->camerax = (2 * (x / (double)data->ray_i->screen_w)) - 1;
		data->ray_i->raydirx = data->ray_i->dirx
			+ data->ray_i->planex * data->ray_i->camerax;
		data->ray_i->raydiry = data->ray_i->diry
			+ data->ray_i->planey * data->ray_i->camerax;
		data->ray_i->mapy = (int)data->ray_i->posy;
		data->ray_i->mapx = (int)data->ray_i->posx;
		setup_dda(data);
		render_line(data, x++);
	}
	mlx_put_image_to_window
		(data->mlx_i->mlx, data->mlx_i->mlx_win, data->mlx_i->img, 0, 0);
	return (0);
}
