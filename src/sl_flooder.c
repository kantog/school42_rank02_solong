/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_flooder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:24:19 by bclaeys           #+#    #+#             */
/*   Updated: 2024/08/26 16:30:01 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	flooder_bitmap_char_handler(t_data *sl, int x, int y, char bit)
{
	sl->flooder_map[y][x] = bit;
	if (bit == 'P')
	{
		sl->current_y = y;
		sl->current_x = x;
		sl->one_player_check++;
	}
	if (bit == 'C')
		sl->collectibles_amount++;
	if (bit == 'E')
		sl->one_exit_check++;
	if (!ft_strrchr("01CEP", bit))
		return (-1);
	return (0);
}

int	ft_create_flooder_map(t_data *sl, int map_fd, char *line, int i)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (line != NULL)
	{
		sl->flooder_map[y] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		while (line[i] != 0 && line[i] != '\n')
			if (flooder_bitmap_char_handler(sl, x++, y, line[i++]) == -1)
				return (-1);
		sl->flooder_map[y][x] = '\0';
		x = 0;
		y++;
		i = 0;
		free(line);
		line = get_next_line(map_fd);
	}
	free(line);
	sl->flooder_map[y] = NULL;
	if (sl->one_player_check == 1 && sl->one_exit_check == 1)
		return (1);
	return (-1);
}

int	ft_flooder(t_data *sl, int x, int y, int collectibles_amount)
{
	if (sl->flooder_map[y][x] == 'C')
		collectibles_amount--;
	if (sl->flooder_map[y][x] == '1' || sl->flooder_map[y][x] == '2')
		return (collectibles_amount);
	sl->flooder_map[y][x] = '2';
	collectibles_amount = ft_flooder(sl, x, y + 1, collectibles_amount);
	collectibles_amount = ft_flooder(sl, x + 1, y, collectibles_amount);
	collectibles_amount = ft_flooder(sl, x, y - 1, collectibles_amount);
	collectibles_amount = ft_flooder(sl, x - 1, y, collectibles_amount);
	return (collectibles_amount);
}

int	ft_check_rect_walls(t_data *sl, int i, int y_amount)
{
	int	len_1st_line;

	while (sl->flooder_map[0][i])
		if (sl->flooder_map[0][i++] != '1')
			return (-1);
	len_1st_line = i;
	i = 0;
	while (sl->flooder_map[i])
	{
		if (ft_strlen(sl->flooder_map[i]) != len_1st_line
			|| sl->flooder_map[i][0] != '1' || sl->flooder_map[i][len_1st_line
			- 1] != '1')
			return (-1);
		i++;
	}
	y_amount = i - 1;
	i = 0;
	while (i < len_1st_line - 1)
	{
		if (sl->flooder_map[y_amount][i] != '1')
			return (-1);
		i++;
	}
	return (0);
}

int	ft_map_check(t_data *sl, char *map_path)
{
	int		map_fd;
	int		map_check;
	char	*line;

	map_check = 1;
	sl->flooder_map = malloc(sizeof(char *) * (ft_check_map_y_length(map_path) + 1));
	if (!sl->flooder_map)
		return (-1);
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (-1);
	line = get_next_line(map_fd);
	if (ft_create_flooder_map(sl, map_fd, line, 0) != 1
		|| sl->collectibles_amount == 0)
		return (-1);
	close(map_fd);
	if (ft_check_rect_walls(sl, 0, 0) == -1)
		return (-1);
	map_check = ft_flooder(sl, sl->current_x, sl->current_y,
			sl->collectibles_amount);
	sl->current_y = 0;
	sl->current_y = 0;
	return (map_check);
}
