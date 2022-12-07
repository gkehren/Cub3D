/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:58:34 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/07 18:27:34 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	where_ray_facing(t_ray *ray)
{
	printf("rayangle = %f\n", ray->rayangle);
	if (ray->rayangle > 0 && ray->rayangle < PI)
		ray->israyfacingdown = 1;
	else
		ray->israyfacingup = 1;
	if (ray->rayangle < 0.5 * PI || ray->rayangle > 1.5 * PI)
		ray->israyfacingright = 1;
	else
		ray->israyfacingleft = 1;
}

void	find_step(t_cub *cub, t_ray *ray, t_coord *step, t_coord *intercept)
{
	intercept->y = floor((cub->player.y / PIXELS) * PIXELS);
	if (ray->israyfacingdown)
		intercept->y += PIXELS;
	intercept->x = cub->player.x + (intercept->y - cub->player.y) / tan(ray->rayangle);
	step->y = PIXELS;
	if (ray->israyfacingup)
		step->y *= -1;
	step->x = PIXELS / tan(ray->rayangle);
	if ((ray->israyfacingleft && step->x > 0) || (ray->israyfacingright && step->x < 0))
		step->x *= -1;
}

bool	haswallat(t_cub *cub, double x, double y)
{
	if (x < 0 || x > cub->width_map || y < 0 || y > cub->height_map)
		return (true);
	if (cub->map[(int)floor(x) / PIXELS][(int)floor(y) / PIXELS] == '1')
		return (true);
	else
		return (false);
}

void	dda(t_cub *cub, t_ray *ray)
{
	t_coord	intercept;
	t_coord	step;
	t_coord	nexthorztouch;

	ray->rayangle = fabs(ray->rayangle);
	where_ray_facing(ray);
	printf("FACING\n");
	printf("isRayFacingRight ? %d\n", ray->israyfacingright);
	printf("isRayFacingLeft ? %d\n", ray->israyfacingleft);
	printf("isrRayFacingUp ? %d\n", ray->israyfacingup);
	printf("isrRayFacingDown ? %d\n", ray->israyfacingdown);
	printf("\n");
	(void)step;
	(void)intercept;
	(void)cub;
	//find_step(cub, ray, &step, &intercept);
	//nexthorztouch.x = intercept.x;
	//nexthorztouch.y = intercept.y;
	//if (ray->israyfacingup)
	//	nexthorztouch.y--;
	//while (ray->foundhorzWall == false)
	//{
	//	if (haswallat(cub, nexthorztouch.x, nexthorztouch.y))
	//	{
	//		ray->foundhorzWall = true;
	//		ray->wallhitx = nexthorztouch.x;
	//		ray->wallhity = nexthorztouch.y;
	//	}
	//	else
	//	{
	//		nexthorztouch.x += step.x;
	//		nexthorztouch.y += step.y;
	//	}
	//}
	//printf("%f | %f\n", ray->wallhitx, ray->wallhity);
	(void)nexthorztouch;
}
