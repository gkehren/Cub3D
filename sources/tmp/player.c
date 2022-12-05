/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:41:27 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/05 22:16:36 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player(t_cub *cub)
{
	cub->player.width = 1;
	cub->player.height = 1;
	cub->player.turn_x = 0;
	cub->player.turn_y = 0;
	cub->player.rotationangle = PI;
	cub->player.walkspeed = 0.17;
	cub->player.turnspeed = 45 * (PI / 180);
}
