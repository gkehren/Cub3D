/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:38:59 by genouf            #+#    #+#             */
/*   Updated: 2022/12/08 15:37:28 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_rays(t_cub *cub)
{
	int	i;

	i = 0;
	cub->ray = (t_ray *)malloc(sizeof(t_ray) * NUM_RAYS);
	while (i < NUM_RAYS)
	{
		cub->ray[i].distance = 0;
		cub->ray[i].israyfacingdown = 0;
		cub->ray[i].israyfacingleft = 0;
		cub->ray[i].israyfacingright = 0;
		cub->ray[i].israyfacingup = 0;
		cub->ray[i].rayangle = cub->player.rotationangle - (FOV / 2);
		cub->ray[i].vertwallhitcontent = 0;
		cub->ray[i].vertwallhitx = 0;
		cub->ray[i].vertwallhity = 0;
		cub->ray[i].horzwallhitcontent = 0;
		cub->ray[i].horzwallhitx = 0;
		cub->ray[i].horzwallhity = 0;
		cub->ray[i].foundhorzwall = false;
		cub->ray[i].foundvertwall = false;
		i++;
	}
}

void	reinit_ray(t_ray *ray, double rangle)
{
	ray->distance = 0;
	ray->israyfacingdown = 0;
	ray->israyfacingleft = 0;
	ray->israyfacingright = 0;
	ray->israyfacingup = 0;
	ray->vertwallhitcontent = 0;
	ray->vertwallhitx = 0;
	ray->vertwallhity = 0;
	ray->horzwallhitcontent = 0;
	ray->horzwallhitx = 0;
	ray->horzwallhity = 0;
	ray->foundhorzwall = false;
	ray->foundvertwall = false;
	ray->rayangle = rangle;
}
