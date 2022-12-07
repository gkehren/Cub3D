/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:58:34 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/08 00:28:34 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	find_step(t_cub *cub, t_ray *ray, t_coord *step, t_coord *intercept)
{
	t_coord	p;

	p.x = cub->player.x * PIXELS;
	p.y = cub->player.y * PIXELS;
	intercept->y = floor(p.y / PIXELS) * PIXELS;
	if (ray->israyfacingdown == 1)
		intercept->y += PIXELS;
	intercept->x = p.x + (intercept->y - p.y) / tan(ray->rayangle);
	step->y = PIXELS;
	if (ray->israyfacingup == 1)
		step->y *= -1;
	step->x = PIXELS / tan(ray->rayangle);
	if (ray->israyfacingleft && step->x > 0)
		step->x *= -1;
	if (ray->israyfacingright && step->x < 0)
		step->x *= -1;
}

void	find_step_v(t_cub *cub, t_ray *ray, t_coord *step, t_coord *intercept)
{
	t_coord	p;

	p.x = cub->player.x * PIXELS;
	p.y = cub->player.y * PIXELS;
	intercept->x = floor(p.x / PIXELS) * PIXELS;
	if (ray->israyfacingright == 1)
		intercept->x += PIXELS;
	intercept->y = p.y + (intercept->x - p.x) * tan(ray->rayangle);
	step->x = PIXELS;
	if (ray->israyfacingleft == 1)
		step->x *= -1;
	step->y = PIXELS * tan(ray->rayangle);
	if (ray->israyfacingup && step->y > 0)
		step->y *= -1;
	if (ray->israyfacingdown && step->y < 0)
		step->y *= -1;
}

void	find_horz(t_cub *cub, t_coord *intercept, t_coord *step, t_ray *ray)
{
	t_coord	nexthorz;
	double	ytocheck;

	nexthorz = (t_coord){intercept->x, intercept->y};
	while (nexthorz.x >= 0 && nexthorz.x <= (cub->width_map * PIXELS)
		&& nexthorz.y >= 0 && nexthorz.y <= (cub->height_map * PIXELS))
	{
		ytocheck = nexthorz.y;
		if (ray->israyfacingup)
			ytocheck = nexthorz.y - 1;
		if (has_wall_at(cub, nexthorz.x, ytocheck) == true)
		{
			ray->foundhorzwall = true;
			ray->horzwallhitx = nexthorz.x;
			ray->horzwallhity = nexthorz.y;
			ray->horzwallhitcontent = cub->map[(int)floor(ytocheck / PIXELS)]
			[(int)floor(nexthorz.x / PIXELS)];
			break ;
		}
		else
		{
			nexthorz.x += step->x;
			nexthorz.y += step->y;
		}
	}
}

void	find_vert(t_cub *cub, t_coord *intercept, t_coord *step, t_ray *ray)
{
	t_coord	nextvert;
	double	xtocheck;

	nextvert = (t_coord){intercept->x, intercept->y};
	while (nextvert.x >= 0 && nextvert.x <= (cub->width_map * PIXELS)
		&& nextvert.y >= 0 && nextvert.y <= (cub->height_map * PIXELS))
	{
		xtocheck = nextvert.x;
		if (ray->israyfacingleft)
			xtocheck = nextvert.x - 1;
		if (has_wall_at(cub, xtocheck, nextvert.y) == true)
		{
			ray->foundvertwall = true;
			ray->vertwallhitx = nextvert.x;
			ray->vertwallhity = nextvert.y;
			ray->vertwallhitcontent = cub->map[(int)floor(nextvert.y / PIXELS)]
			[(int)floor(xtocheck / PIXELS)];
			break ;
		}
		else
		{
			nextvert.x += step->x;
			nextvert.y += step->y;
		}
	}
}

double	dda(t_cub *cub, t_ray *ray)
{
	t_coord	intercept;
	t_coord	step;

	where_ray_facing(ray);
	find_step(cub, ray, &step, &intercept);
	find_horz(cub, &intercept, &step, ray);
	find_step_v(cub, ray, &step, &intercept);
	find_vert(cub, &intercept, &step, ray);
	if (distance((t_coord){cub->player.x * PIXELS, cub->player.y * PIXELS},
		(t_coord){ray->vertwallhitx, ray->vertwallhity})
		> distance((t_coord){cub->player.x * PIXELS, cub->player.y * PIXELS},
		(t_coord){ray->horzwallhitx, ray->horzwallhity}))
		return (distance((t_coord){cub->player.x * PIXELS,
				cub->player.y * PIXELS},
			(t_coord){ray->horzwallhitx, ray->horzwallhity}));
	else
		return (distance((t_coord){cub->player.x * PIXELS,
				cub->player.y * PIXELS},
			(t_coord){ray->vertwallhitx, ray->vertwallhity}));
}
