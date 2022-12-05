/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:41:27 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/05 12:28:21 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player(t_cub *cub)
{
	cub->player.width = 1;
	cub->player.height = 1;
	cub->player.turndirection = 0;
	cub->player.walkdirection = 0;
	cub->player.rotationangle = PI / 2;
	cub->player.walkspeed = 100;
	cub->player.turnspeed = 45 * (PI / 180);
}
