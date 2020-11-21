/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 12:33:02 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/10 14:46:43 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(t_all *all)
{
	int		y;
	int		x;

	all->check_one_player = 0;
	y = -1;
	while (all->map.map[++y])
	{
		x = -1;
		while (all->map.map[y][++x])
			if (0 != ft_strchr("NSEW", all->map.map[y][x]))
			{
				all->player.y = y * SCALE + (SCALE / 2);
				all->player.x = x * SCALE + (SCALE / 2);
				if (all->map.map[y][x] == 'N')
					all->player.dir = M_PI / 2;
				else if (all->map.map[y][x] == 'S')
					all->player.dir = 3 * M_PI / 2;
				else if (all->map.map[y][x] == 'E')
					all->player.dir = 0;
				else if (all->map.map[y][x] == 'W')
					all->player.dir = M_PI;
				all->check_one_player++;
			}
	}
}

void	find_sprites(t_all *all)
{
	int		x;
	int		y;

	all->sprites_amount = 0;
	y = -1;
	while (all->map.map[++y])
	{
		x = -1;
		while (all->map.map[y][++x])
			if (all->map.map[y][x] == '2')
				all->sprites_amount++;
	}
	if (all->sprites_amount > 0)
		if (!(all->sprite = (t_sprite*)malloc(sizeof(t_sprite)
											* all->sprites_amount)))
			put_error("Error\n	--malloc from sprites don't work--\n", all);
}

void	get_sprites(t_all *all)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	y = -1;
	if (all->sprites_amount > 0)
		while (all->map.map[++y])
		{
			x = -1;
			while (all->map.map[y][++x])
				if (all->map.map[y][x] == '2')
				{
					all->sprite[i].x = x * SCALE + (SCALE / 2);
					all->sprite[i].y = y * SCALE + (SCALE / 2);
					i++;
				}
		}
}

int		parser(int *fd, t_all *all)
{
	init_before_pars(all);
	parser_config(fd, all);
	parser_map(fd, all);
	close(*fd);
	init_after_pars(all);
	find_player(all);
	if (all->check_one_player > 1)
		put_error("Error\n	--Too many players!--\n", all);
	else if (all->check_one_player == 0)
		put_error("Error\n	--Player not found!--\n", all);
	find_sprites(all);
	get_sprites(all);
	return (0);
}
