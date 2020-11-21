/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:11:03 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/21 13:01:38 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			key_press(int key, t_all *all)
{
	if (key == 1 || key == 125)
		all->player.down = 1;
	else if (key == 13 || key == 126)
		all->player.up = 1;
	else if (key == 0)
		all->player.left = 1;
	else if (key == 2)
		all->player.right = 1;
	else if (key == 123)
		all->player.leftrot = 1;
	else if (key == 124)
		all->player.rightrot = 1;
	else if (key == 53)
		put_error("You press ESC! Bye-bye!\n", all);
	else if (key == 257 || key == 258)
		all->player.run = 1;
	return (0);
}

int			key_release(int key, t_all *all)
{
	if (key == 1 || key == 125)
		all->player.down = 0;
	else if (key == 13 || key == 126)
		all->player.up = 0;
	else if (key == 0)
		all->player.left = 0;
	else if (key == 2)
		all->player.right = 0;
	else if (key == 123)
		all->player.leftrot = 0;
	else if (key == 124)
		all->player.rightrot = 0;
	else if (key == 257 || key == 258)
		all->player.run = 0;
	return (0);
}

void		rotation(t_player *player, float speed)
{
	if (player->rightrot == 1)
		player->dir -= M_PI * (speed / 6);
	if (player->leftrot == 1)
		player->dir += M_PI * (speed / 6);
}

void		up_down_left_right(t_player *player, float speed)
{
	if (player->up == 1)
	{
		player->y -= sin(player->dir) * SCALE * speed;
		player->x += cos(player->dir) * SCALE * speed;
	}
	if (player->down == 1)
	{
		player->y += sin(player->dir) * SCALE * speed;
		player->x -= cos(player->dir) * SCALE * speed;
	}
	if (player->left == 1)
	{
		player->y -= sin(player->dir + M_PI / 2) * SCALE * speed;
		player->x += cos(player->dir + M_PI / 2) * SCALE * speed;
	}
	if (player->right == 1)
	{
		player->y += sin(player->dir + M_PI / 2) * SCALE * speed;
		player->x -= cos(player->dir + M_PI / 2) * SCALE * speed;
	}
}

int			move(t_all *all)
{
	float	speed;

	speed = 0.1;
	if (all->player.run == 1)
		speed = 0.3;
	up_down_left_right(&all->player, speed);
	rotation(&all->player, speed);
	return (0);
}
