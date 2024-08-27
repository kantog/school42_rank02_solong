/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:24:20 by bclaeys           #+#    #+#             */
/*   Updated: 2024/08/27 11:11:09 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  SO_LONG_H
# define  SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <stdio.h>
# include <stdlib.h>
# define WALL_PATH "./textures/wall.xpm"
# define FLOOR_PATH "./textures/floor.xpm"
# define TILE 79
# define PLAYER_RIGHT_PATH "./textures/player_rightward.xpm"
# define PLAYER_LEFT_PATH "./textures/player_leftward.xpm"
# define COLLECTIBLE_PATH "./textures/collectible.xpm"
# define EXIT_PATH "./textures/exit.xpm"

typedef struct s_data
{
	void	*mlx;
	void	*img;
	void	*mlx_win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		y_axis;
	int		x_axis;
	char	**map;
	char	**flooder_map;
	void	*wall;
	void	*floor;
	void	*collectible;
	void	*exit;
	void	*player;
	int		tile_size;
	int		current_y;
	int		current_x;
	int		collectibles_amount;
	int		exit_binary;
	int		steps;
	int		one_player_check;
	int		one_exit_check;
	char	*map_path;
}			t_data;

// helper functions //

void		ft_set_paths(t_data *sl);
void		ft_set_to_null(t_data *game);
void		sl_free_map(char **map);
int			sl_free_all(t_data *sl);
int			ft_check_map_y_length(t_data *sl, char *map_path);
int			ft_check_map_x_length(t_data *sl, char *map_path);
int			ft_init(t_data *game);
int			ft_click_close(t_data *sl);

// flooder function //

int	ft_map_check(t_data *sl);

// map creating function //

int			ft_create_map(t_data *sl);

#endif
