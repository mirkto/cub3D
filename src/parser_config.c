/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:10:33 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/28 17:10:40 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_resolution(t_all *all, char *read_line)
{
	int		wid;
	int		hei;
	int		len;

	len = 1;
	while (read_line[len] == ' ' || read_line[len] == '\t')
		len++;
	if (!ft_isdigit(read_line[len]))
		put_error("Error\n	--Not correct resolution--\n", all);
	wid = ft_atoi(&read_line[len]);
	len += ft_nbrlen(wid);
	while (read_line[len] == ' ' || read_line[len] == '\t')
		len++;
	if (!ft_isdigit(read_line[len]))
		put_error("Error\n	--Not correct resolution--\n", all);
	hei = ft_atoi(&read_line[len]);
	if (ft_nbrlen(wid) > 4 || ft_nbrlen(hei) > 4 || wid < 0 || hei < 0
		|| (len += ft_nbrlen(hei)) != (int)ft_strlen(read_line))
		put_error("Error\n	--Not correct resolution--\n", all);
	if (all->pars.screen_width == -1 && all->pars.screen_height == -1)
		all->pars.screen_width = wid;
	else
		put_error("Error\n	--Duplicate parameters--\n", all);
	all->pars.screen_height = hei;
	free(read_line);
}

void	parse_tex_path(t_all *all, char *read_line)
{
	int		len;
	int		i;
	char	*buff;

	if (ft_strncmp(read_line, "NO ", 3) == 0)
		i = 0;
	else if (ft_strncmp(read_line, "SO ", 3) == 0)
		i = 1;
	else if (ft_strncmp(read_line, "WE ", 3) == 0)
		i = 2;
	else if (ft_strncmp(read_line, "EA ", 3) == 0)
		i = 3;
	else if (ft_strncmp(read_line, "S ", 2) == 0)
		i = 4;
	len = 2;
	while (read_line[len] == ' ' || read_line[len] == '\t')
		len++;
	buff = ft_strdup(&read_line[len]);
	if (ft_strncmp(&buff[ft_strlen(buff) - 4], ".xpm", 4) != 0)
		put_error("Error\n	--Not valid texture file or path--\n", all);
	if (all->tex[i].path == NULL)
		all->tex[i].path = buff;
	else
		put_error("Error\n	--Duplicate parameters--\n", all);
	free(read_line);
}

void	parse_color(t_all *all, char *read_line)
{
	int		len;
	int		rgb[3];
	int		i;

	len = 1;
	i = -1;
	while (++i < 3)
	{
		while (read_line[len] == ' ' || read_line[len] == '\t')
			len++;
		if (!ft_isdigit(read_line[len]))
			put_error("Error\n	--Not correct color--\n", all);
		rgb[i] = ft_atoi(&read_line[len]);
		len += ft_nbrlen(rgb[i]);
		while (read_line[len] != ',' && i < 2)
			len++;
		len++;
	}
	if (--len != (int)ft_strlen(read_line))
		put_error("Error\n	--Not correct color--\n", all);
	mix_color(rgb, all, read_line);
	free(read_line);
}

void	parse_config_line(t_all *all, char *read_line)
{
	read_line = ft_strtrim(read_line, "\t \n\v\f\r");
	if (ft_strncmp(read_line, "R ", 2) == 0)
		parse_resolution(all, read_line);
	else if (ft_strncmp(read_line, "F ", 2) == 0 ||
			ft_strncmp(read_line, "C ", 2) == 0)
		parse_color(all, read_line);
	else if (ft_strncmp(read_line, "NO ", 3) == 0 ||
			ft_strncmp(read_line, "SO ", 3) == 0 ||
			ft_strncmp(read_line, "WE ", 3) == 0 ||
			ft_strncmp(read_line, "EA ", 3) == 0 ||
			ft_strncmp(read_line, "S ", 2) == 0)
		parse_tex_path(all, read_line);
}

void	parser_config(int *fd, t_all *all)
{
	char	*read_line;
	int		gnl_result;

	while ((gnl_result = get_next_line(*fd, &read_line)) > 0)
	{
		if (ft_strlen(read_line) > 0)
			parse_config_line(all, read_line);
		free(read_line);
		read_line = NULL;
		if (1 == is_parsing_complete(all))
			break ;
	}
	free(read_line);
	if (gnl_result == 0)
		put_error("Error\n	--Some parameters are missed--\n", all);
	if (gnl_result < 0)
		put_error("Error\n	--Error when reading line--\n", all);
}
