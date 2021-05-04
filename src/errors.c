#include "cub3d.h"

void	ft_clean_all(t_all *all)
{
	int		i;

	free(all->sprite);
	free(all->map.map);
	free(all->data.win);
	free(all->data.img);
	free(all->data.mlx);
	all->data.addr = NULL;
	if (all->screenshot == 1)
		all->data.addr_int = NULL;
	i = -1;
	while (++i < 5)
	{
		free(all->tex[i].img);
		all->tex[i].path = NULL;
		all->tex[i].addr = NULL;
	}
}

int		ft_close(t_all *all)
{
	if (all->check == 1)
		ft_clean_all(all);
	exit(0);
	return (0);
}

void	put_error(char *message, t_all *all)
{
	write(2, message, ft_strlen(message));
	ft_close(all);
}
