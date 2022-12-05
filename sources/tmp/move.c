/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:35:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/05 19:31:27 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_down(char **map, t_player *player)
{
	if (map[(int)player->x + 1][(int)player->y] != '1')
		player->x += player->walkspeed;
	player->turndirection = DOWN;
}

void	move_up(char **map, t_player *player)
{
	if (map[(int)player->x - 1][(int)player->y] != '1')
		player->x -= player->walkspeed;
	player->turndirection = UP;
}

void	move_right(char **map, t_player *player)
{
	if (map[(int)player->x][(int)player->y + 1] != '1')
		player->y += player->walkspeed;
	player->turndirection = RIGHT;
}

void	move_left(char **map, t_player *player)
{
	if (map[(int)player->x][(int)player->y - 1] != '1')
		player->y -= player->walkspeed;
	player->turndirection = LEFT;
}

int	move_player(int keycode, t_cub *cub)
{
	t_player	bplayer;

	bplayer = cub->player;
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
	cast_all_rays(cub);
	printf("%f | %f\n", cub->player.x, cub->player.y);
	render_minimap(cub, &cub->player, &bplayer, 0);
	return (0);
}
