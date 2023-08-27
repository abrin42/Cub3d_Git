/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <abrin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:49:31 by abrin             #+#    #+#             */
/*   Updated: 2023/08/27 03:16:33 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_pix_color(t_texture *text, int x, int y)
{
	return (*(int *)(text->addr \
			+ (4 * text->width * y) \
			+ (4 * x)));
}

void	setup_texture(t_data *data)
{
	setup_texture2(data);
	data->map_i->cell_color = data->map_i->c1[0] * 256 * 256
		+ data->map_i->c1[1] * 256 + data->map_i->c1[2];
	data->map_i->floor_color = data->map_i->f1[0] * 256 * 256
		+ data->map_i->f1[1] * 256 + data->map_i->f1[2];
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

void	setup_texture2(t_data *data)
{
	data->map_i->no.img = mlx_xpm_file_to_image
		(data->mlx_i->mlx, data->map_i->no1,
			&(data->map_i->no.width), &(data->map_i->no.height));
	data->map_i->no.addr = mlx_get_data_addr
		(data->map_i->no.img, &(data->map_i->no.bpp),
			&(data->map_i->no.line_len), &(data->map_i->no.endian));
	data->map_i->so.img = mlx_xpm_file_to_image
		(data->mlx_i->mlx, data->map_i->so1, &(data->map_i->so.width),
			&(data->map_i->so.height));
	data->map_i->so.addr = mlx_get_data_addr
		(data->map_i->so.img, &(data->map_i->so.bpp),
			&(data->map_i->so.line_len), &(data->map_i->so.endian));
	data->map_i->we.img = mlx_xpm_file_to_image
		(data->mlx_i->mlx, data->map_i->we1, &(data->map_i->we.width),
			&(data->map_i->we.height));
	data->map_i->we.addr = mlx_get_data_addr
		(data->map_i->we.img, &(data->map_i->we.bpp),
			&(data->map_i->we.line_len), &(data->map_i->we.endian));
	data->map_i->ea.img = mlx_xpm_file_to_image
		(data->mlx_i->mlx, data->map_i->ea1, &(data->map_i->ea.width),
			&(data->map_i->ea.height));
	data->map_i->ea.addr = mlx_get_data_addr
		(data->map_i->ea.img, &(data->map_i->ea.bpp),
			&(data->map_i->ea.line_len), &(data->map_i->ea.endian));
}
