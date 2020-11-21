/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:56:15 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/18 18:56:38 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_map_symbols(t_all *all)
{
	int		y;
	int		x;

	y = -1;
	while (all->map.map[++y])
	{
		x = -1;
		while (all->map.map[y][++x])
		{
			if (0 != ft_strchr("02NSEW", all->map.map[y][x]))
			{
				if (y == 0 || x == 0 || y == all->map.max_y - 1 ||
					x == all->map.max_x - 1)
					put_error("Error\n	--!Not valid map!--\n", all);
				if (0 == ft_strchr("102NSEW", all->map.map[y - 1][x]))
					put_error("Error\n	--Not valid map--\n", all);
				if (0 == ft_strchr("102NSEW", all->map.map[y][x - 1]))
					put_error("Error\n	--Not valid map--\n", all);
				if (0 == ft_strchr("102NSEW", all->map.map[y + 1][x]))
					put_error("Error\n	--Not valid map--\n", all);
				if (0 == ft_strchr("102NSEW", all->map.map[y][x + 1]))
					put_error("Error\n	--Not valid map--\n", all);
			}
		}
	}
}

void		make_map(t_all *all, t_list *head)
{
	int		y;
	int		x;
	t_list	*tmp;

	y = 0;
	tmp = head;
	while (all->map.map[y])
	{
		ft_strcpy(all->map.map[y], tmp->content);
		x = -1;
		while (++x < all->map.max_x)
		{
			if (!all->map.map[y][x])
				all->map.map[y][x] = ' ';
		}
		all->map.map[y][all->map.max_x] = '\0';
		tmp = tmp->next;
		y++;
	}
}

void		init_map(t_all *all)
{
	int		y;

	if (!(all->map.map = (char **)malloc(sizeof(char *) *
	(all->map.max_y + 1))))
		put_error("Error\n	--Malloc error--\n", all);
	all->map.map[all->map.max_y] = NULL;
	y = -1;
	while (++y < all->map.max_y)
	{
		if (!(all->map.map[y] = (char *)malloc(sizeof(char) *
		(all->map.max_x + 1))))
			put_error("Error\n	--Malloc error--\n", all);
		ft_bspace(all->map.map[y], all->map.max_x);
		all->map.map[y][all->map.max_x] = '\0';
	}
}

void		get_map(t_all *all, int *fd)
{
	int		len_x;
	char	*read_line;
	t_list	*head;

	get_next_line(*fd, &read_line);
	check_trash(all, read_line);
	while (ft_strlen(read_line) == 0)
	{
		free(read_line);
		get_next_line(*fd, &read_line);
	}
	while ((len_x = ft_strlen(read_line)) > 0)
	{
		all->map.max_y++;
		if (all->map.max_x < len_x)
			all->map.max_x = len_x;
		ft_putendl_fd(read_line, 1);
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(read_line)));
		free(read_line);
		get_next_line(*fd, &read_line);
	}
	free(read_line);
	init_map(all);
	make_map(all, head);
	ft_lstclear(&head, free);
}

void		parser_map(int *fd, t_all *all)
{
	get_map(all, fd);
	close(*fd);
	check_map_symbols(all);
}
