/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:14:30 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/23 14:14:33 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			sort_sprite(t_all *all)
{
	int			i;
	t_sprite	tmp;

	i = -1;
	while (++i < all->sprites_amount)
	{
		if (all->sprite[i].dist < all->sprite[i + 1].dist)
		{
			tmp = all->sprite[i];
			all->sprite[i] = all->sprite[i + 1];
			all->sprite[i + 1] = tmp;
			i = -1;
		}
	}
}

float			fix_delta_angle(float fov_start, float sprite_dir)
{
	float		delta;

	delta = fov_start - sprite_dir;
	if (delta <= -M_PI)
		delta = 2 * M_PI + delta;
	else if (delta >= M_PI)
		delta = delta - 2 * M_PI;
	return (delta);
}

void			get_sprite_params(t_all *all)
{
	double		start;
	int			i;

	start = all->player.dir + (FOV / 2);
	i = -1;
	while (++i < all->sprites_amount)
	{
		all->sprite[i].dir = atan2(all->player.y - all->sprite[i].y,
									all->sprite[i].x - all->player.x);
		all->sprite[i].dist = hypot(all->player.y - all->sprite[i].y,
									all->player.x - all->sprite[i].x);
		all->sprite[i].dist *= cos(all->player.dir + (FOV / 2)
													- all->player.dir);
		all->sprite[i].size = (int)((SCALE / all->sprite[i].dist)
										* all->player.projection_plane);
		all->sprite[i].delta = fix_delta_angle(all->player.dir + (FOV / 2),
													all->sprite[i].dir);
		all->sprite[i].hor_offset = (all->sprite[i].delta / (FOV /
						all->pars.screen_width) - all->sprite[i].size / 2);
		all->sprite[i].vert_offset = (all->pars.screen_height / 2
												- all->sprite[i].size / 2);
	}
	sort_sprite(all);
}

int				sprite_color(t_all *all, int y_line, int i)
{
	int			color;
	int			y_texture;
	int			x_texture;

	y_texture = y_line * (all->tex[4].height - 1) / (all->sprite[i].size - 1);
	x_texture = (all->ray.x_line - all->sprite[i].hor_offset)
						* (all->tex[4].width - 1) / (all->sprite[i].size - 1);
	if (x_texture > 63)
		x_texture = 63;
	color = *(all->tex[4].addr + (int)((int)y_texture * (all->tex[4].lenl /
			sizeof(int)) + x_texture * ((all->tex[4].bpp / 8) / sizeof(int))));
	return (color);
}

void			draw_sprite(t_all *all)
{
	int			i;
	int			y_line;
	int			color;

	i = -1;
	while (++i < all->sprites_amount)
	{
		if (all->sprite[i].size > all->pars.screen_height)
			all->sprite[i].size = 0;
		if (all->sprite[i].hor_offset < 0 && all->sprite[i].hor_offset >
											all->pars.screen_width - 1)
			all->sprite[i].size = 0;
		if (all->ray.x_line >= all->sprite[i].hor_offset &&
			all->ray.x_line <= all->sprite[i].hor_offset + all->sprite[i].size
			&& all->sprite[i].dist < all->ray.ray_len)
		{
			y_line = -1;
			while (++y_line < all->sprite[i].size)
				if ((color = sprite_color(all, y_line, i)) != 0x000000)
					my_mlx_pixel_put(&all->data, all->ray.x_line,
							(int)(all->sprite[i].vert_offset + y_line), color);
		}
	}
}
