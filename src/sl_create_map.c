/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_create_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:17:57 by bclaeys           #+#    #+#             */
/*   Updated: 2024/08/27 17:52:57 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_bitmap_char_handler(t_data *sl, int x, int y, char bit)
{
	sl->map[(y / TILE) - 1][(x / TILE) - 1] = bit;
	if (bit == 'P')
	{
		sl->current_y = y;
		sl->current_x = x;
	}
	if (bit == 'C')
		sl->collectibles_amount++;
}

static void	sl_put_tile(t_data *sl, char bit, int x, int y)
{
	if (bit == '1')
		mlx_put_image_to_window(sl->mlx, sl->mlx_win, sl->wall, x, y);
	if (bit == '0')
		mlx_put_image_to_window(sl->mlx, sl->mlx_win, sl->floor, x, y);
	if (bit == 'C')
		mlx_put_image_to_window(sl->mlx, sl->mlx_win, sl->collectible, x, y);
	if (bit == 'P')
		mlx_put_image_to_window(sl->mlx, sl->mlx_win, sl->player, x, y);
	if (bit == 'E')
		mlx_put_image_to_window(sl->mlx, sl->mlx_win, sl->exit, x, y);
}

static void	ft_parse_bitmap(t_data *sl, int map_fd, char *line, int i)
{
	int	y;
	int	x;

	y = TILE;
	x = TILE;
	while (line != NULL)
	{
		sl->map[y / TILE - 1] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!sl->map[y / TILE - 1])
			ft_malloc_error(sl, line, map_fd);
		while (line[i] != 0 && line[i] != '\n')
		{
			sl_put_tile(sl, line[i], x, y);
			ft_bitmap_char_handler(sl, x, y, line[i++]);
			x += TILE;
		}
		sl->map[(y / TILE) - 1][(x / TILE) - 1] = '\0';
		x = TILE;
		y += TILE;
		i = 0;
		free(line);
		line = get_next_line(map_fd);
	}
	free(line);
	sl->map[y / TILE - 1] = NULL;
}

static int	ft_render_map(t_data *sl)
{
	int		map_fd;
	char	*line;

	line = NULL;
	map_fd = open(sl->map_path, O_RDONLY);
	sl->map = malloc(sizeof(char *) * (ft_check_map_y_length(sl, sl->map_path)
				+ 1));
	if (!sl->map)
		ft_malloc_error(sl, line, map_fd);
	if (map_fd == -1)
	{
		sl_free_all(sl);
		exit(-1);
	}
	line = get_next_line(map_fd);
	ft_parse_bitmap(sl, map_fd, line, 0);
	close(map_fd);
	return (0);
}

int	ft_create_map(t_data *sl)
{
	if (ft_render_map(sl) == -1)
	{
		ft_printf("Error opening file\n");
		exit(1);
	}
	else
		ft_printf("Creating map\n");
	return (0);
}
