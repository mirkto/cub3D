/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:34:22 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/22 13:34:26 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			background(t_all *all)
{
	int		x;
	int		y;
	int		color;

	color = all->pars.color_top;
	y = -1;
	while (++y < all->pars.screen_height / 2)
	{
		x = -1;
		while (++x < all->pars.screen_width)
			my_mlx_pixel_put(&all->data, x, y, color);
	}
	color = all->pars.color_bot;
	while (++y < all->pars.screen_height)
	{
		x = -1;
		while (++x < all->pars.screen_width)
			my_mlx_pixel_put(&all->data, x, y, color);
	}
}

int				render_next_frame(t_all *all)
{
	if (all->screenshot == 1)
	{
		background(all);
		draw_scene(all);
	}
	else
	{
		mlx_do_sync(all->data.mlx);
		move(all);
		all->player.dir = all->player.dir > 2 * M_PI ?
						all->player.dir -= 2 * M_PI : all->player.dir;
		all->player.dir = all->player.dir < -2 * M_PI ?
						all->player.dir += 2 * M_PI : all->player.dir;
		background(all);
		draw_scene(all);
		mlx_put_image_to_window(all->data.mlx, all->data.win,
												all->data.img, 0, 0);
	}
	return (0);
}

void			cub3d(t_all *all)
{
	all->data.mlx = mlx_init();
	all->data.img = mlx_new_image(all->data.mlx, all->pars.screen_width,
												all->pars.screen_height);
	all->data.addr = mlx_get_data_addr(all->data.img, &all->data.bpp,
										&all->data.lenl, &all->data.en);
	textures_init(all);
	if (all->screenshot == 1)
		make_screenshot(all);
	all->data.win = mlx_new_window(all->data.mlx, all->pars.screen_width,
							all->pars.screen_height, "cub3D");
	mlx_hook(all->data.win, 2, 1L << 0, key_press, all);
	mlx_hook(all->data.win, 3, 1L << 1, key_release, all);
	mlx_hook(all->data.win, 17, 1L << 17, ft_close, all);
	mlx_loop_hook(all->data.mlx, render_next_frame, all);
	mlx_loop(all->data.mlx);
}

int				main(int argc, char **argv)
{
	t_all	all;
	int		fd;

	all.check = 0;
	all.screenshot = 0;
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
		all.screenshot = 1;
	else if (argc != 2)
		put_error("Error\n	--Not correct argumet--\n", &all);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
		put_error("Error\n	--Argumet is not *.cub--\n", &all);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		put_error("Error\n	--Map is not find--\n", &all);
	parser(&fd, &all);
	all.check = 1;
	cub3d(&all);
	return (0);
}
