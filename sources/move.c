/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:35:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/07 14:54:05 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_down(char **map, t_player *player)
{
	if (map[(int)(player->y + player->walkspeed
			* player->turn_y)][(int)player->x] != '1')
		player->x += player->walkspeed * player->turn_x;
	if (map[(int)(player->y)][(int)(player->x + player->turn_x
				* player->walkspeed)] != '1')
		player->y += player->walkspeed * player->turn_y;
}

void	move_up(char **map, t_player *player)
{
	if (map[(int)player->y][(int)(player->x - player->walkspeed
			* player->turn_x)] != '1')
		player->x -= player->walkspeed * player->turn_x;
	if (map[(int)(player->y - player->walkspeed
			* player->turn_y)][(int)(player->x)] != '1')
		player->y -= player->walkspeed * player->turn_y;
}

//void	move_right(char **map, t_player *player)
//{
//	if (map[(int)(player->x)][(int)(player->y + player->walkspeed)] != '1')
//		player->y += player->walkspeed;
//}

//void	move_left(char **map, t_player *player)
//{
//	if (map[(int)player->x][(int)(player->y - player->walkspeed)] != '1')
//		player->y -= player->walkspeed;
//}

void	move_camera_right(t_player *player)
{
	t_player	bplayer;

	bplayer = *player;
	player->turn_y = cos(-(player->turnspeed)) * player->turn_y
		- sin(-(player->turnspeed)) * player->turn_x;
	player->turn_x = sin(-(player->turnspeed)) * bplayer.turn_y
		+ cos(-(player->turnspeed)) * player->turn_x;
}

void	move_camera_left(t_player *player)
{
	t_player	bplayer;

	bplayer = *player;
	player->turn_y = cos(player->turnspeed) * player->turn_y
		- sin(player->turnspeed) * player->turn_x;
	player->turn_x = sin(player->turnspeed) * bplayer.turn_y
		+ cos(player->turnspeed) * player->turn_x;
}

int	move_player(int keycode, t_cub *cub)
{
	if (keycode == 115)
		move_down(cub->map, &cub->player);
	else if (keycode == 119)
		move_up(cub->map, &cub->player);
	else if (keycode == 100)
		move_camera_right(&cub->player);
		//move_right(cub->map, &cub->player);
	else if (keycode == 97)
		move_camera_left(&cub->player);
		//move_left(cub->map, &cub->player);
	if (keycode == 65307)
		close_window(cub);
	printf("%f | %f\n", cub->player.x, cub->player.y);
	render_minimap(cub, &cub->player);
	return (0);
}
