/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:32:05 by bclaeys           #+#    #+#             */
/*   Updated: 2024/08/27 11:10:10 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_put_floor(t_data *sl, int keycode)
{
	if (sl->map[(sl->current_y / TILE) - 1][(sl->current_x / TILE) - 1] == 'E'
		&& sl->exit_binary == 0)
		mlx_put_image_to_window(sl->mlx, sl->mlx_win, sl->exit, sl->current_x,
			sl->current_y);
	else
		mlx_put_image_to_window(sl->mlx, sl->mlx_win, sl->floor, sl->current_x,
			sl->current_y);
	if (keycode == XK_d)
		sl->current_x += TILE;
	if (keycode == XK_s)
		sl->current_y += TILE;
	if (keycode == XK_w)
		sl->current_y -= TILE;
	if (keycode == XK_a)
		sl->current_x -= TILE;
	mlx_put_image_to_window(sl->mlx, sl->mlx_win, sl->player, sl->current_x,
		sl->current_y);
}

int	ft_wall_check(t_data *sl, int keycode)
{
	if (keycode == XK_d)
		if (sl->map[sl->current_y / TILE - 1][sl->current_x / TILE] == '1')
			return (-1);
	if (keycode == XK_s)
		if (sl->map[sl->current_y / TILE][sl->current_x / TILE - 1] == '1')
			return (-1);
	if (keycode == XK_w)
		if (sl->map[sl->current_y / TILE - 2][sl->current_x / TILE - 1] == '1')
			return (-1);
	if (keycode == XK_a)
		if (sl->map[sl->current_y / TILE - 1][sl->current_x / TILE - 2] == '1')
			return (-1);
	return (0);
}

void	ft_handle_movement(t_data *sl, int keycode)
{
	if (ft_wall_check(sl, keycode) == -1)
		return ;
	ft_put_floor(sl, keycode);
	ft_printf("Turn %i\n", sl->steps);
	sl->steps++;
	if (sl->map[sl->current_y / TILE - 1][sl->current_x / TILE - 1] == 'C')
	{
		sl->collectibles_amount--;
		sl->map[sl->current_y / TILE - 1][sl->current_x / TILE - 1] = '0';
	}
	if (sl->map[sl->current_y / TILE - 1][sl->current_x / TILE - 1] == 'E'
		&& sl->collectibles_amount == 0)
		sl->exit_binary = 1;
}

int	ft_handle_input(int keycode, t_data *sl)
{
	sl->tile_size = TILE;
	if (keycode == XK_d || keycode == XK_s || keycode == XK_a
		|| keycode == XK_w)
		ft_handle_movement(sl, keycode);
	if (keycode == XK_Escape || sl->exit_binary == 1)
	{
		ft_printf("Exiting\n");
		sl_free_all(sl);
		exit(1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	game;

	ft_set_to_null(&game);
	if (argc < 2)
	{
		ft_printf("No map given.\n");
		return (0);
	}
	game.map_path = argv[1];
	if (ft_map_check(&game) != 0)
	{
		sl_free_all(&game);	
		return (ft_printf("Error\nInvalid map\n") - 17);
	}
	if (ft_init(&game) == 0)
		return (0);
	ft_create_map(&game);
	ft_printf("writing screen\n");
	mlx_key_hook(game.mlx_win, ft_handle_input, &game);
	mlx_hook(game.mlx_win, 17, 0, ft_click_close, &game);
	mlx_loop(game.mlx);
}
