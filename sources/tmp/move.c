/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:35:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/06 13:32:09 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_down(char **map, t_player *player)
{
	if (map[(int)(player->x + player->walkspeed)][(int)player->y] != '1')
		player->x += player->walkspeed;
}

void	move_up(char **map, t_player *player)
{
	if (map[(int)(player->x - player->walkspeed)][(int)player->y] != '1')
		player->x -= player->walkspeed;
}

void	move_right(char **map, t_player *player)
{
	if (map[(int)(player->x)][(int)(player->y + player->walkspeed)] != '1')
		player->y += player->walkspeed;
}

void	move_left(char **map, t_player *player)
{
	if (map[(int)player->x][(int)(player->y - player->walkspeed)] != '1')
		player->y -= player->walkspeed;
}

/*-----CAMERA-----*/
void	move_camera_right(t_player *player)
{
	t_player	bplayer;

	bplayer = *player;
	player->turn_x = cos(player->turnspeed) * player->turn_x
		- sin(player->turnspeed) * player->turn_y;
	player->turn_y = sin(player->turnspeed) * bplayer.turn_x
		+ cos(player->turnspeed) * player->turn_y;
}

void	move_camera_left(t_player *player)
{
	t_player	bplayer;

	bplayer = *player;
	player->turn_x = cos(-(player->turnspeed)) * player->turn_x
		- sin(-(player->turnspeed)) * player->turn_y;
	player->turn_y = sin(-(player->turnspeed)) * bplayer.turn_x
		+ cos(-(player->turnspeed)) * player->turn_y;
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
	cast_all_rays(cub);
	printf("%f | %f\n", cub->player.x, cub->player.y);
	render_minimap(cub, &cub->player);
	return (0);
}
