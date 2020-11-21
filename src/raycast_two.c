/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:36:24 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/28 19:36:25 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		choose_texture(t_all *all)
{
	if (all->ray.what_intersection == 1 && all->ray.is_right)
		return (0);
	if (all->ray.what_intersection == 0 && all->ray.is_up)
		return (1);
	if (all->ray.what_intersection == 1 && all->ray.is_left)
		return (2);
	if (all->ray.what_intersection == 0 && all->ray.is_down)
		return (3);
	return (4);
}

void	draw_line_two(t_all *all, float slice_h, int tex_x, float height_diff)
{
	int		y_start;
	int		y_end;
	int		color;
	float	step_y;
	int		ind;

	ind = 0;
	if (slice_h > all->pars.screen_height)
	{
		ind = (slice_h - all->pars.screen_height) / 2 - 1;
		height_diff = all->pars.screen_height - slice_h;
		slice_h = all->pars.screen_height;
	}
	step_y = all->tex[all->tex_num].height / (slice_h - height_diff);
	y_start = ((all->pars.screen_height - slice_h) / 2);
	y_end = all->pars.screen_height - y_start;
	while (y_start < y_end - 1)
	{
		color = *(all->tex[all->tex_num].addr + (int)((int)(step_y * ind) *
				all->tex[all->tex_num].lenl / sizeof(int) + tex_x *
				(all->tex[all->tex_num].bpp / 8) / sizeof(int)));
		my_mlx_pixel_put(&all->data, all->ray.x_line, y_start, color);
		++y_start;
		++ind;
	}
}

void	draw_line(t_all *all)
{
	float	slice_height;
	int		texture_x;
	float	height_diff;

	all->tex_num = -1;
	slice_height = 0;
	height_diff = 0;
	all->ray.ray_intersection = (all->ray.what_intersection == 0) ?
							all->ray.intersection_x : all->ray.intersection_y;
	all->tex_num = choose_texture(all);
	texture_x = (int)all->ray.ray_intersection % SCALE %
											all->tex[all->tex_num].width;
	if (all->ray.ray_len != 0)
		slice_height = (int)(SCALE * all->player.projection_plane /
			all->ray.ray_len);
	draw_line_two(all, slice_height, texture_x, height_diff);
}
