/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 00:24:32 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/09 18:48:55 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	return_ray(t_cub *cub, t_ray *ray)
{
	if (ray->foundhorzwall == false)
		return (distance((t_coord){cub->player.x * PIXELS,
				cub->player.y * PIXELS},
			(t_coord){ray->vertwallhitx, ray->vertwallhity}));
	else if (ray->foundvertwall == false)
		return (distance((t_coord){cub->player.x * PIXELS,
				cub->player.y * PIXELS},
			(t_coord){ray->horzwallhitx, ray->horzwallhity}));
	if (distance((t_coord){cub->player.x * PIXELS, cub->player.y * PIXELS},
		(t_coord){ray->vertwallhitx, ray->vertwallhity})
		> distance((t_coord){cub->player.x * PIXELS, cub->player.y * PIXELS},
		(t_coord){ray->horzwallhitx, ray->horzwallhity}))
	{
		ray->closest = 0;
		return (distance((t_coord){cub->player.x * PIXELS,
				cub->player.y * PIXELS},
			(t_coord){ray->horzwallhitx, ray->horzwallhity}));
	}
	else
	{
		ray->closest = 1;
		return (distance((t_coord){cub->player.x * PIXELS,
				cub->player.y * PIXELS},
			(t_coord){ray->vertwallhitx, ray->vertwallhity}));
	}
}

void	where_ray_facing(t_ray *ray)
{
	ray->rayangle = remainder(ray->rayangle, PI * 2);
	if (ray->rayangle < 0)
		ray->rayangle = PI * 2 + ray->rayangle;
	if (ray->rayangle > 0 && ray->rayangle < PI)
		ray->israyfacingdown = 1;
	else
		ray->israyfacingup = 1;
	if (ray->rayangle < 0.5 * PI || ray->rayangle > 1.5 * PI)
		ray->israyfacingright = 1;
	else
		ray->israyfacingleft = 1;
}

bool	has_wall_at(t_cub *cub, double x, double y)
{
	if (x < 0 || x > (cub->width_map * PIXELS) || y < 0
		|| y > (cub->height_map * PIXELS))
		return (true);
	if (cub->map[(int)floor(y / PIXELS)][(int)floor(x / PIXELS)] != '0')
		return (true);
	else
		return (false);
}
