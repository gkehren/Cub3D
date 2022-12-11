/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:35:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/11 23:00:16 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_forward(t_player *player, t_cub *cub)
{
	if (has_wall_at(cub, PIXELS * (player->x - player->walkspeed
				* player->turn_x) - PADDING, PIXELS * player->y) == false
		&& has_wall_at(cub, PIXELS * (player->x - player->walkspeed
				* player->turn_x) + PADDING, PIXELS * player->y) == false)
		player->x -= player->walkspeed * player->turn_x;
	if (has_wall_at(cub, PIXELS * player->x, PIXELS * (player->y
				- player->walkspeed * player->turn_y) - PADDING) == false
		&& has_wall_at(cub, PIXELS * player->x, PIXELS * (player->y
				- player->walkspeed * player->turn_y) + PADDING) == false)
		player->y -= player->walkspeed * player->turn_y;
}

void	move_backward(t_player *player, t_cub *cub)
{
	if (has_wall_at(cub, PIXELS * (player->x + player->walkspeed
				* player->turn_x) + PADDING, PIXELS * player->y) == false
		&& has_wall_at(cub, PIXELS * (player->x + player->walkspeed
				* player->turn_x) - PADDING, PIXELS * player->y) == false)
		player->x += player->walkspeed * player->turn_x;
	if (has_wall_at(cub, PIXELS * player->x, PIXELS * (player->y
				+ player->walkspeed * player->turn_y) + PADDING) == false
		&& has_wall_at(cub, PIXELS * player->x, PIXELS * (player->y
				+ player->walkspeed * player->turn_y) - PADDING) == false)
		player->y += player->walkspeed * player->turn_y;
}

void	move_right(t_player *player, t_cub *cub)
{
	if (has_wall_at(cub, PIXELS * (player->x - (player->walkspeed
					* sin(player->rotationangle) / 2)) + PADDING,
			PIXELS * player->y) == false)
		player->x -= player->walkspeed * sin(player->rotationangle) / 2;
	if (has_wall_at(cub, PIXELS * player->x, PIXELS * (player->y
				+ (player->walkspeed * cos(player->rotationangle) / 2))
			- PADDING) == false)
		player->y += player->walkspeed * cos(player->rotationangle) / 2;
}

void	move_left(t_player *player, t_cub *cub)
{
	if (has_wall_at(cub, PIXELS * (player->x + (player->walkspeed
					* sin(player->rotationangle) / 2)) - PADDING,
			PIXELS * player->y) == false)
		player->x += player->walkspeed * sin(player->rotationangle) / 2;
	if (has_wall_at(cub, PIXELS * player->x, PIXELS * (player->y
				- (player->walkspeed * cos(player->rotationangle) / 2))
			+ PADDING) == false)
		player->y -= player->walkspeed * cos(player->rotationangle) / 2;
}
