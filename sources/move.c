/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:35:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/02 02:06:13 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_down(char **map, t_player *player)
{
	if (map[player->x + 1][player->y] != '1')
		player->x++;
}

void	move_up(char **map, t_player *player)
{
	if (map[player->x - 1][player->y] != '1')
		player->x--;
}

void	move_right(char **map, t_player *player)
{
	if (map[player->x][player->y + 1] != '1')
		player->y++;
}

void	move_left(char **map, t_player *player)
{
	if (map[player->x][player->y - 1] != '1')
		player->y--;
}

int	move_player(int keycode, t_cub *cub)
{
	if (keycode == 115)
		move_down(cub->map, &cub->player);
	else if (keycode == 119)
		move_up(cub->map, &cub->player);
	else if (keycode == 100)
		move_right(cub->map, &cub->player);
	else if (keycode == 97)
		move_left(cub->map, &cub->player);
	if (keycode == 65307)
		close_window(cub);
	render_map(cub->map, cub, &cub->player);
	return (0);
}
