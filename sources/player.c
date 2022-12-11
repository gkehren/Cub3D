/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:41:27 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/11 22:54:15 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	if (keycode == XK_s || keycode == XK_Down)
		move_backward(&cub->player, cub);
	else if (keycode == XK_w || keycode == XK_Up)
		move_forward(&cub->player, cub);
	else if (keycode == XK_d)
		move_right(&cub->player, cub);
	else if (keycode == XK_a)
		move_left(&cub->player, cub);
	if (keycode == XK_Right)
		move_camera_right(&cub->player);
	else if (keycode == XK_Left)
		move_camera_left(&cub->player);
	if (keycode == XK_Escape)
		close_window(cub);
	render(cub, &cub->player);
	return (0);
}

void	set_orientation_player(t_cub *cub)
{
	if (cub->map[(int)cub->player.y][(int)cub->player.x] == 'N')
	{
		cub->player.turn_x = 0;
		cub->player.turn_y = 1;
		cub->player.rotationangle = -PI / 2;
	}
	else if (cub->map[(int)cub->player.y][(int)cub->player.x] == 'S')
	{
		cub->player.turn_x = 0;
		cub->player.turn_y = -1;
		cub->player.rotationangle = PI / 2;
	}
	else if (cub->map[(int)cub->player.y][(int)cub->player.x] == 'W')
	{
		cub->player.turn_x = 1;
		cub->player.turn_y = 0;
		cub->player.rotationangle = PI;
	}
	else if (cub->map[(int)cub->player.y][(int)cub->player.x] == 'E')
	{
		cub->player.turn_x = -1;
		cub->player.turn_y = 0;
		cub->player.rotationangle = 2 * PI;
	}
}

void	init_player(t_cub *cub)
{
	set_orientation_player(cub);
	cub->map[(int)cub->player.y][(int)cub->player.x] = '0';
	cub->player.walkspeed = 0.17;
	cub->player.turnspeed = 0.02;
}
