/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:41:27 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/07 11:10:21 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_cub *cub)
{
	cub->player.width = 1;
	cub->player.height = 1;
	if (cub->map[(int)cub->player.x][(int)cub->player.y] == 'N')
	{
		cub->player.turn_x = 1;
		cub->player.turn_y = 0;
	}
	else if (cub->map[(int)cub->player.x][(int)cub->player.y] == 'S')
	{
		cub->player.turn_x = -1;
		cub->player.turn_y = 0;
	}
	else if (cub->map[(int)cub->player.x][(int)cub->player.y] == 'W')
	{
		cub->player.turn_x = 0;
		cub->player.turn_y = 1;
	}
	else if (cub->map[(int)cub->player.x][(int)cub->player.y] == 'E')
	{
		cub->player.turn_x = 0;
		cub->player.turn_y = -1;
	}
	cub->player.rotationangle = PI;
	cub->player.walkspeed = 0.17;
	cub->player.turnspeed = 0.5;
}
