/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:39:03 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/20 16:39:24 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				int_to_char(unsigned char *c, int i)
{
	c[0] = (unsigned char)(i);
	c[1] = (unsigned char)(i >> 8);
	c[2] = (unsigned char)(i >> 16);
	c[3] = (unsigned char)(i >> 24);
}

int					bmp_header(int fd, int h, int w, int padsize)
{
	unsigned char	header[54];
	int				filesize;

	filesize = 54 + (w * 3 * h) + (padsize * h);
	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_to_char(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	int_to_char(header + 18, w);
	int_to_char(header + 22, h);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (!(write(fd, header, 54) < 0));
}

int					bmp_data(int fd, t_all *all, int padsize)
{
	unsigned char	zero[3];
	int				x;
	int				y;
	int				pixel;

	y = all->pars.screen_height;
	ft_bzero(zero, 3);
	while (--y >= 0)
	{
		x = -1;
		while (++x < all->pars.screen_width)
		{
			pixel = *(all->data.addr_int + x + y * all->data.lenl / 4);
			if (write(fd, &pixel, 3) < 0)
				return (0);
		}
		if (padsize > 0 && write(fd, &zero, padsize) < 0)
			return (0);
	}
	return (1);
}

int					take_screenshot(t_all *all)
{
	int				padsize;
	int				fd;

	render_next_frame(all);
	padsize = (4 - ((int)all->pars.screen_width * 3) % 4) % 4;
	if ((fd = open("screenshot.bmp",
			O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND)) < 0)
		return (0);
	bmp_header(fd, all->pars.screen_height, all->pars.screen_width, padsize);
	bmp_data(fd, all, padsize);
	close(fd);
	return (1);
}

void				make_screenshot(t_all *all)
{
	all->data.addr_int = (int *)mlx_get_data_addr(all->data.img,
						&all->data.bpp, &all->data.lenl, &all->data.en);
	if (!take_screenshot(all))
		put_error("ERROR\n  --Couldn't create/open screenshot.bmp--\n", all);
	put_error("Screenshot create!\n", all);
}
