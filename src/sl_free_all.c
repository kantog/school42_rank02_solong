/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:38:23 by bclaeys           #+#    #+#             */
/*   Updated: 2024/08/27 17:28:09 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

int	sl_free_all(t_data *sl)
{
	sl_free_map(sl->flooder_map);
	sl_free_map(sl->map);
	if (sl->img)
		mlx_destroy_image(sl->mlx, sl->img);
	if (sl->collectible)
		mlx_destroy_image(sl->mlx, sl->collectible);
	if (sl->floor)
		mlx_destroy_image(sl->mlx, sl->floor);
	if (sl->player)
		mlx_destroy_image(sl->mlx, sl->player);
	if (sl->exit)
		mlx_destroy_image(sl->mlx, sl->exit);
	if (sl->wall)
		mlx_destroy_image(sl->mlx, sl->wall);
	if (sl->mlx_win)
		mlx_destroy_window(sl->mlx, sl->mlx_win);
	if (sl->mlx)
	{
		mlx_destroy_display(sl->mlx);
		free(sl->mlx);
	}
	return (0);
}

int	ft_click_close(t_data *sl)
{
	sl_free_all(sl);
	exit(1);
}

void	ft_check_path_ber(char *map_path)
{
	int		i;
	int		j;
	int		x;
	char	*ber;

	ber = ".ber";
	i = ft_strlen(map_path) - 4;
	j = ft_strlen(map_path);
	x = 0;
	while (i != j)
	{
		if (map_path[i] != ber[x])
		{
			ft_printf("Your map needs a .ber extension.\n");
			exit(1);
		}
		i++;
		x++;
	}
}

void	ft_malloc_error(t_data *sl, char *line, int map_fd)
{
	sl_free_all(sl);
	close(map_fd);
	free(line);
	ft_printf("Error.\nMalloc failed.\n");
	exit(1);
}
