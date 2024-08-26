/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:38:23 by bclaeys           #+#    #+#             */
/*   Updated: 2024/08/25 16:47:19 by bclaeys          ###   ########.fr       */
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
	mlx_destroy_image(sl->mlx, sl->wall);
	mlx_destroy_image(sl->mlx, sl->collectible);
	mlx_destroy_image(sl->mlx, sl->floor);
	mlx_destroy_image(sl->mlx, sl->player);
	mlx_destroy_image(sl->mlx, sl->exit);
	mlx_destroy_image(sl->mlx, sl->img);
	mlx_destroy_window(sl->mlx, sl->mlx_win);
	mlx_destroy_display(sl->mlx);
	free(sl->mlx);
	return (0);
}
