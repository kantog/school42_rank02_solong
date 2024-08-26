/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:26:30 by bclaeys           #+#    #+#             */
/*   Updated: 2024/08/26 17:39:46 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_set_paths(t_data *sl)
{
	sl->wall = mlx_xpm_file_to_image(sl->mlx, WALL_PATH, &sl->tile_size,
			&sl->tile_size);
	sl->floor = mlx_xpm_file_to_image(sl->mlx, FLOOR_PATH, &sl->tile_size,
			&sl->tile_size);
	sl->collectible = mlx_xpm_file_to_image(sl->mlx, COLLECTIBLE_PATH,
			&sl->tile_size, &sl->tile_size);
	sl->player = mlx_xpm_file_to_image(sl->mlx, PLAYER_RIGHT_PATH,
			&sl->tile_size, &sl->tile_size);
	sl->exit = mlx_xpm_file_to_image(sl->mlx, EXIT_PATH, &sl->tile_size,
			&sl->tile_size);
}

void	ft_set_to_null(t_data *game)
{
	game->mlx = NULL;
	game->img = NULL;
	game->mlx_win = NULL;
	game->addr = NULL;
	game->bits_per_pixel = 0;
	game->line_length = 0;
	game->endian = 0;
	game->y_axis = 0;
	game->x_axis = 0;
	game->map = NULL;
	game->wall = NULL;
	game->floor = NULL;
	game->collectible = NULL;
	game->exit = NULL;
	game->player = NULL;
	game->tile_size = 0;
	game->current_y = 0;
	game->current_x = 0;
	game->collectibles_amount = 0;
	game->exit_binary = 0;
	game->steps = 0;
	game->one_player_check = 0;
	game->one_exit_check = 0;
	game->flooder_map = NULL;
}

int	ft_check_map_y_length(char *map_path)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}

int	ft_check_map_x_length(char *map_path)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	free(line);
	close(fd);
	return (i);
}

int	ft_init(t_data *game, char *map_path)
{
	game->y_axis = (ft_check_map_y_length(map_path) + 2) * TILE;
	game->x_axis = (ft_check_map_x_length(map_path) + 2) * TILE;
	game->collectibles_amount = 0;
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (0);
	game->mlx_win = mlx_new_window(game->mlx, game->x_axis, game->y_axis,
		"so_long");
	if (game->mlx_win == NULL)
		return (sl_free_all(game));
	game->img = mlx_new_image(game->mlx, game->x_axis, game->y_axis);
	if (game->img == NULL)
		return (sl_free_all(game));
	return (1);
}
