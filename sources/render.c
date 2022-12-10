/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/10 12:41:24 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_pixels(int size, t_img *img, t_coord p, int color)
{
	int	end_col;
	int	end_line;
	int	i;
	int	j;

	end_line = (p.x + 1) * size;
	end_col = (p.y + 1) * size;
	i = p.y * size;
	while (i < end_col)
	{
		j = p.x * size;
		while (j < end_line)
		{
			my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

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

void	render_minimap(t_cub *cub, t_player *player)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == '1')
				render_pixels(MAP, &cub->minimap, (t_coord){j, i}, BLACK);
			else if (cub->map[i][j] != ' ')
				render_pixels(MAP, &cub->minimap, (t_coord){j, i}, WHITE);
		}
	}
	mlx_clear_window(cub->mlx, cub->win);
	print_square(player->x * MAP, player->y * MAP, 7, &cub->minimap);
	if (player->update == true)
		render_rays(cub, player, cub->num_rays);
	else
		render_rays(cub, player, cub->num_rays / 8);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->game.img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img,
		WIDTH - (cub->width_map * MAP), 0);
}
