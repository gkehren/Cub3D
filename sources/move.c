/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:35:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/08 15:52:58 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_down(t_player *player, t_cub *cub)
{
	if (has_wall_at(cub, PIXELS * (player->x + player->walkspeed
				* player->turn_x), PIXELS * player->y) == false)
		player->x += player->walkspeed * player->turn_x;
	if (has_wall_at(cub, PIXELS * player->x, PIXELS * (player->y
				+ player->walkspeed * player->turn_y)) == false)
		player->y += player->walkspeed * player->turn_y;
}

void	move_up(t_player *player, t_cub *cub)
{
	if (has_wall_at(cub, PIXELS * (player->x - player->walkspeed
				* player->turn_x), PIXELS * player->y) == false)
		player->x -= player->walkspeed * player->turn_x;
	if (has_wall_at(cub, PIXELS * player->x, PIXELS * (player->y
				- player->walkspeed * player->turn_y)) == false)
		player->y -= player->walkspeed * player->turn_y;
}

void	move_camera_right(t_player *player)
{
	t_player	bplayer;

	bplayer = *player;
	player->turn_y = cos(-(player->turnspeed)) * player->turn_y
		- sin(-(player->turnspeed)) * player->turn_x;
	player->turn_x = sin(-(player->turnspeed)) * bplayer.turn_y
		+ cos(-(player->turnspeed)) * player->turn_x;
	player->turndirection = 1;
	player->rotationangle += player->turndirection * player->turnspeed;
}

void	move_camera_left(t_player *player)
{
	t_player	bplayer;

	bplayer = *player;
	player->turn_y = cos(player->turnspeed) * player->turn_y
		- sin(player->turnspeed) * player->turn_x;
	player->turn_x = sin(player->turnspeed) * bplayer.turn_y
		+ cos(player->turnspeed) * player->turn_x;
	player->turndirection = -1;
	player->rotationangle += player->turndirection * player->turnspeed;
}

int	move_player(int keycode, t_cub *cub)
{
	if (keycode == 115)
		move_down(&cub->player, cub);
	else if (keycode == 119)
		move_up(&cub->player, cub);
	else if (keycode == 100)
		move_camera_right(&cub->player);
	else if (keycode == 97)
		move_camera_left(&cub->player);
	if (keycode == 65307)
		close_window(cub);
	render_minimap(cub, &cub->player);
	return (0);
}
