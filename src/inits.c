/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 11:58:48 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/23 11:58:51 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	textures_init(t_all *all)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (!(all->tex[i].img = mlx_xpm_file_to_image(all->data.mlx,
				all->tex[i].path, &(all->tex[i].width), &(all->tex[i].height))))
			put_error("Error\n	--Not valid texture file or path--\n", all);
		all->tex[i].addr = (int *)mlx_get_data_addr(all->tex[i].img,
						&all->tex[i].bpp, &all->tex[i].lenl, &all->tex[i].en);
	}
}

void	init_after_pars(t_all *all)
{
	all->pars.max_screen_width = 320;
	all->pars.max_screen_height = 240;
	mlx_get_screen_size(all->data.mlx, &all->pars.max_screen_width,
										&all->pars.max_screen_height);
	if (all->pars.screen_width > all->pars.max_screen_width)
		all->pars.screen_width = all->pars.max_screen_width;
	if (all->pars.screen_height > all->pars.max_screen_height)
		all->pars.screen_height = all->pars.max_screen_height;
	all->player.projection_plane = (all->pars.screen_width / 2) /
													(tan(FOV / 2));
}

void	init_before_pars(t_all *all)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		all->tex[i].path = NULL;
		all->tex[i].img = NULL;
		all->tex[i].addr = NULL;
	}
	all->pars.color_top = -1;
	all->pars.color_bot = -1;
	all->pars.screen_width = -1;
	all->pars.screen_height = -1;
	all->player.up = 0;
	all->player.down = 0;
	all->player.left = 0;
	all->player.right = 0;
	all->player.leftrot = 0;
	all->player.rightrot = 0;
	all->player.run = 0;
	all->map.max_x = 0;
	all->map.max_y = 0;
}
