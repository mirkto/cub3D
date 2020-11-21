/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:35:44 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/28 19:35:47 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	horizontal_intersection(t_all *all, float start)
{
	float	x_hor;
	float	y_hor;
	float	x_diff;
	float	y_diff;

	x_hor = 0;
	y_hor = 0;
	y_hor = (int)(all->player.y / SCALE) * SCALE;
	y_hor += (all->ray.is_up) ? -0.001 : SCALE;
	x_hor = all->player.x + (all->player.y - y_hor) / tan(start);
	x_diff = SCALE / tan(start);
	x_diff *= (all->ray.is_left && x_diff > 0) ? -1 : 1;
	x_diff *= (all->ray.is_right && x_diff < 0) ? -1 : 1;
	y_diff = (all->ray.is_up) ? -SCALE : SCALE;
	while (y_hor / SCALE >= 0 && y_hor / SCALE < all->map.max_y &&
		x_hor / SCALE >= 0 && x_hor / SCALE < all->map.max_x &&
		all->map.map[(int)(y_hor / SCALE)][(int)(x_hor / SCALE)] != '1')
	{
		y_hor += y_diff;
		x_hor += x_diff;
	}
	all->ray.intersection_x = x_hor;
	return (fabs((all->player.y - y_hor) / sin(start)));
}

static float	vertical_intersection(t_all *all, float start)
{
	float	x_vert;
	float	y_vert;
	float	y_diff;
	float	x_diff;

	x_vert = 0;
	y_vert = 0;
	x_vert = (int)(all->player.x / SCALE) * SCALE;
	x_vert += (all->ray.is_right) ? SCALE : -0.001;
	y_vert = all->player.y + (all->player.x - x_vert) * tan(start);
	y_diff = SCALE * tan(start);
	y_diff *= (all->ray.is_up && y_diff > 0) ? -1 : 1;
	y_diff *= (all->ray.is_down && y_diff < 0) ? -1 : 1;
	x_diff = (all->ray.is_left) ? -SCALE : SCALE;
	while (y_vert / SCALE >= 0 && y_vert / SCALE < all->map.max_y &&
		x_vert / SCALE >= 0 && x_vert / SCALE < all->map.max_x &&
		all->map.map[(int)(y_vert / SCALE)][(int)(x_vert / SCALE)] != '1')
	{
		x_vert += x_diff;
		y_vert += y_diff;
	}
	all->ray.intersection_y = y_vert;
	return (fabs((all->player.x - x_vert) / cos(start)));
}

static void		get_ray_len(t_all *all, float start)
{
	float	ray_hor;
	float	ray_vert;

	ray_hor = 0;
	ray_vert = 0;
	all->ray.what_intersection = 0;
	if (all->ray.is_up || all->ray.is_down)
		ray_hor = horizontal_intersection(all, start);
	if (all->ray.is_left || all->ray.is_right)
		ray_vert = vertical_intersection(all, start);
	if (ray_vert == 0)
		all->ray.ray_len = ray_hor;
	else if (ray_hor == 0)
	{
		all->ray.ray_len = ray_vert;
		all->ray.what_intersection = 1;
	}
	else
	{
		all->ray.ray_len = (ray_vert < ray_hor) ? (ray_vert * cos(start -
			all->player.dir)) : (ray_hor * cos(start - all->player.dir));
		all->ray.what_intersection = (ray_vert < ray_hor) ? 1 : 0;
	}
}

void			get_ray_direction(t_all *all, float start)
{
	all->ray.is_right = 0;
	all->ray.is_left = 0;
	all->ray.is_up = 0;
	all->ray.is_down = 0;
	if (cos(start) > 0)
		all->ray.is_right = 1;
	else if (cos(start) < 0)
		all->ray.is_left = 1;
	if (sin(start) > 0)
		all->ray.is_up = 1;
	else if (sin(start) < 0)
		all->ray.is_down = 1;
}

void			draw_scene(t_all *all)
{
	float	start;
	float	end;

	start = all->player.dir - (FOV / 2);
	end = all->player.dir + (FOV / 2);
	all->ray.x_line = all->pars.screen_width - 1;
	get_sprite_params(all);
	while (start <= end && all->ray.x_line >= 0)
	{
		get_ray_direction(all, start);
		get_ray_len(all, start);
		draw_line(all);
		draw_sprite(all);
		start += (FOV) / all->pars.screen_width;
		all->ray.x_line--;
	}
}
