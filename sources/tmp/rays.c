/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:41:36 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/05 16:25:42 by gkehren          ###   ########.fr       */
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
		{
			ray->wallhitcontent = 1;
			render_image(cub, GREEN, (int)ray->wallhitx, (int)ray->wallhity);
		}
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
		{
			ray->wallhitcontent = 1;
			render_image(cub, GREEN, (int)ray->wallhitx, (int)ray->wallhity);
		}
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
		{
			ray->wallhitcontent = 1;
			render_image(cub, GREEN, (int)ray->wallhitx, (int)ray->wallhity);
		}
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
		{
			ray->wallhitcontent = 1;
			render_image(cub, GREEN, (int)ray->wallhitx, (int)ray->wallhity);
		}
	}
}

int	cast_all_rays(t_cub *cub)
{
	int	i;
	float	rayangle;

	i = 0;
	rayangle = 0;
	while (i < NUM_RAYS)
	{
		if (cub->player.turndirection == UP)
			cast_ray_up(cub, rayangle, &cub->ray[i]);
		else if (cub->player.turndirection == DOWN)
			cast_ray_down(cub, rayangle, &cub->ray[i]);
		else if (cub->player.turndirection == RIGHT)
			cast_ray_right(cub, rayangle, &cub->ray[i]);
		else if (cub->player.turndirection == LEFT)
			cast_ray_left(cub, rayangle, &cub->ray[i]);
		i++;
	}
	(void)cub;
	return (0);
}
