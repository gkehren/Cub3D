/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:41:27 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/09 16:22:28 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	cub->player.update = true;
	cub->player.walkspeed = 0.17;
	cub->player.turnspeed = 0.02;
}
