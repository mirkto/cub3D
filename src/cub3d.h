/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngonzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:28:12 by ngonzo            #+#    #+#             */
/*   Updated: 2020/10/10 14:18:27 by ngonzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx_mms/mlx.h"
# include <fcntl.h>
# include <math.h>

# define SCALE 64
# define FOV (M_PI / 3)

# define ESC 53
# define UP 126
# define W 13
# define DOWN 125
# define S 1
# define LEFT 123
# define A 0
# define RIGHT 124
# define D 2
# define R_SHIFT 258
# define L_SHIFT 257

typedef struct	s_data{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			*addr_int;
	int			bpp;
	int			lenl;
	int			en;
}				t_data;

typedef struct	s_player {
	float		y;
	float		x;
	int			projection_plane;
	float		dir;
	float		start;
	float		end;
	char		up;
	char		down;
	char		left;
	char		right;
	char		leftrot;
	char		rightrot;
	char		run;
}				t_player;

typedef	struct	s_map {
	char		**map;
	int			max_y;
	int			max_x;
}				t_map;

typedef struct	s_pars {
	int			color_top;
	int			color_bot;
	int			screen_width;
	int			screen_height;
	int			max_screen_width;
	int			max_screen_height;
	int			ray_step;
}				t_pars;

typedef struct	s_ray
{
	int			is_left;
	int			is_right;
	int			is_up;
	int			is_down;
	float		intersection_x;
	float		intersection_y;
	int			what_intersection;
	float		ray_intersection;
	float		ray_len;
	int			x_line;
}				t_ray;

typedef struct	s_texture
{
	void		*img;
	char		*path;
	int			*addr;
	int			bpp;
	int			lenl;
	int			en;
	int			width;
	int			height;
}				t_texture;

typedef struct	s_sprite
{
	float		x;
	float		y;
	float		dist;
	float		dir;
	float		hor_offset;
	float		vert_offset;
	int			size;
	float		delta;
}				t_sprite;

typedef struct	s_all {
	t_data		data;
	t_player	player;
	t_map		map;
	t_pars		pars;
	t_ray		ray;
	t_texture	tex[5];
	t_sprite	*sprite;
	int			screenshot;
	int			sprites_amount;
	int			check_one_player;
	int			check;
	int			tex_num;
}				t_all;

void			init_before_pars(t_all *all);
int				parser(int *fd, t_all *all);
void			parser_config(int *fd, t_all *all);
int				is_parsing_complete(t_all *all);
void			parser_map(int *fd, t_all *all);
void			init_after_pars(t_all *all);

void			textures_init(t_all *all);
void			make_screenshot(t_all *all);
int				key_press(int key, t_all *all);
int				key_release(int key, t_all *all);

int				render_next_frame(t_all *all);
int				move(t_all *all);
void			draw_scene(t_all *all);
void			draw_line(t_all *all);
void			get_sprite_params(t_all *all);
void			draw_sprite(t_all *all);

int				ft_close(t_all *all);
void			put_error(char *message, t_all *all);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_bspace(void *s, size_t n);
void			mix_color(int *rgb, t_all *all, char *read_line);
void			check_trash(t_all *all, char *read_line);

#endif
