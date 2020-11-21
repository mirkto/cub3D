/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:13:07 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/28 17:13:09 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->lenl + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int		is_parsing_complete(t_all *all)
{
	if (all->pars.screen_width == -1)
		return (0);
	if (all->pars.screen_height == -1)
		return (0);
	if (all->pars.color_top == -1)
		return (0);
	if (all->pars.color_bot == -1)
		return (0);
	if (all->tex[0].path == NULL)
		return (0);
	if (all->tex[1].path == NULL)
		return (0);
	if (all->tex[2].path == NULL)
		return (0);
	if (all->tex[3].path == NULL)
		return (0);
	if (all->tex[4].path == NULL)
		return (0);
	return (1);
}

void	ft_bspace(void *s, size_t n)
{
	char	*tmp;
	size_t	i;

	tmp = s;
	i = 0;
	while (i < n)
	{
		tmp[i] = ' ';
		i++;
	}
}

void	mix_color(int *rgb, t_all *all, char *read_line)
{
	int		color;

	if (rgb[0] > 255 || rgb[0] < 0 || rgb[1] > 255 || rgb[1] < 0
		|| rgb[2] > 255 || rgb[2] < 0)
		put_error("Error\n	--Not valid color--\n", all);
	color = rgb[0] << 16 | rgb[1] << 8 | rgb[2] << 0;
	if (ft_strncmp(read_line, "F ", 2) == 0 && all->pars.color_bot == -1)
		all->pars.color_bot = color;
	else if (ft_strncmp(read_line, "C ", 2) == 0 && all->pars.color_top == -1)
		all->pars.color_top = color;
	else
		put_error("Error\n	--Duplicate parameters--\n", all);
}

void	check_trash(t_all *all, char *read_line)
{
	int		i;

	i = -1;
	while (++i < (int)ft_strlen(read_line))
		if (!ft_strchr("\n\t 102NSEW", read_line[i]))
			put_error("Error\n	--Trash after parameters--\n", all);
}
