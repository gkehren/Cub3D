/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/10 18:26:20 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_up_txt(t_cub *cub, t_ray *ray, t_proj *proj)
{
	if (ray->foundhorzwall == true && ray->closest == 0)
	{
		proj->offset = (int)floor(ray->horzwallhitx) % PIXELS;
		if (ray->israyfacingup == 1)
			proj->txt = cub->img[0];
		else
			proj->txt = cub->img[1];
	}
	else
	{
		proj->offset = (int)floor(ray->vertwallhity) % PIXELS;
		if (ray->israyfacingleft == 1)
			proj->txt = cub->img[2];
		else
			proj->txt = cub->img[3];
	}
	proj->screen = &cub->game;
}

void	projection(t_cub *cub, t_ray *ray, int idcol)
{
	double	distance_proj_plane;
	double	wall_strip_height;
	t_coord	begin;
	t_coord	begin2;
	t_proj	proj;

	distance_proj_plane = (WIDTH / 2) / tan(cub->fov / 2);
	wall_strip_height = (PIXELS / ray->distance) * distance_proj_plane;
	begin.x = idcol * WALL_STRIP_WIDTH;
	begin.y = (HEIGHT / 2) - (wall_strip_height / 2);
	set_up_txt(cub, ray, &proj);
	print_rectangle_text(begin, (t_dim){WALL_STRIP_WIDTH,
		wall_strip_height}, &proj);
	begin2.x = begin.x;
	begin2.y = 0;
	print_rectangle(begin2, (t_dim){WALL_STRIP_WIDTH, begin.y},
		&cub->game, (cub->rgb_ceiling[0] << 16) + (cub->rgb_ceiling[1] << 8)
		+ cub->rgb_ceiling[2]);
	begin2.y = begin.y + wall_strip_height;
	print_rectangle(begin2, (t_dim){WALL_STRIP_WIDTH, HEIGHT - begin2.y},
		&cub->game, (cub->rgb_floor[0] << 16) + (cub->rgb_floor[1] << 8)
		+ cub->rgb_floor[2]);
}

void	render_rays(t_cub *cub, t_player *player, int num_rays)
{
	double	rangle;
	int		i;

	rangle = player->rotationangle - (cub->fov / 2);
	i = 0;
	while (i < num_rays)
	{
		reinit_ray(&cub->ray[i], rangle);
		dda(cub, &cub->ray[i]);
		cub->ray[i].distance *= cos(rangle - player->rotationangle);
		projection(cub, &cub->ray[i], i);
		rangle += cub->fov / cub->num_rays;
		i++;
	}
}

void	render(t_cub *cub, t_player *player)
{
	if (cub->width_map * MAP > WIDTH / 2 || cub->height_map * MAP > HEIGHT / 3)
		render_minimap(cub, player);
	else
		full_render_minimap(cub, player);
	mlx_clear_window(cub->mlx, cub->win);
	if (player->update == true)
		render_rays(cub, player, cub->num_rays);
	else
		render_rays(cub, player, cub->num_rays / PIXELS);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->game.img, 0, 0);
	if (cub->width_map * MAP > WIDTH / 2 || cub->height_map * MAP > HEIGHT / 3)
		mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img,
			WIDTH - (20 * MAP), 0);
	else
		mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img,
			WIDTH - (cub->width_map * MAP), 0);
}
