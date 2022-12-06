/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:41:36 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/06 13:32:16 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
		cub->ray[i].rayangle = 0;
		cub->ray[i].wallhitcontent = 0;
		cub->ray[i].wallhitx = 0;
		cub->ray[i].wallhity = 0;
		cub->ray[i].washitvertical = 0;
		i++;
	}
	cub->player.rotationangle = 0;
}

void	cast_ray_up(t_cub *cub, float rayangle, t_ray *ray)
{
	ray->wallhitx = cub->player.x - rayangle;
	ray->wallhity = cub->player.y;
	ray->wallhitcontent = 0;
	while (ray->wallhitcontent == 0)
	{
		ray->wallhitx -= 1;
		if (cub->map[(int)ray->wallhitx][(int)ray->wallhity] == '1')
			ray->wallhitcontent = 1;
	}
}

void	cast_ray_down(t_cub *cub, float rayangle, t_ray *ray)
{
	ray->wallhitx = cub->player.x + rayangle;
	ray->wallhity = cub->player.y;
	ray->wallhitcontent = 0;
	while (ray->wallhitcontent == 0)
	{
		ray->wallhitx += 1;
		if (cub->map[(int)ray->wallhitx][(int)ray->wallhity] == '1')
			ray->wallhitcontent = 1;
	}
}

void	cast_ray_right(t_cub *cub, float rayangle, t_ray *ray)
{
	ray->wallhitx = cub->player.x;
	ray->wallhity = cub->player.y + rayangle;
	ray->wallhitcontent = 0;
	while (ray->wallhitcontent == 0)
	{
		ray->wallhity += 1;
		if (cub->map[(int)ray->wallhitx][(int)ray->wallhity] == '1')
			ray->wallhitcontent = 1;
	}
}

void	cast_ray_left(t_cub *cub, float rayangle, t_ray *ray)
{
	ray->wallhitx = cub->player.x;
	ray->wallhity = cub->player.y - rayangle;
	ray->wallhitcontent = 0;
	while (ray->wallhitcontent == 0)
	{
		ray->wallhity -= 1;
		if (cub->map[(int)ray->wallhitx][(int)ray->wallhity] == '1')
			ray->wallhitcontent = 1;
	}
}

int	cast_all_rays(t_cub *cub)
{
	int		i;

	i = 0;
	while (i < NUM_RAYS)
	{
		i++;
	}
	(void)cub;
	return (0);
}
