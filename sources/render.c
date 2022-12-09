/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/09 18:36:34 by genouf           ###   ########.fr       */
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

void	projection(t_cub *cub, int idcol)
{
	double	distance_proj_plane;
	double	wall_strip_height;
	t_coord	begin;
	t_coord	begin2;
	int 	offset;
	t_img	txt;

	distance_proj_plane = (WIDTH / 2) / tan(FOV / 2);
	wall_strip_height = (PIXELS / cub->ray[idcol].distance) * distance_proj_plane;
	begin.x = idcol * WALL_STRIP_WIDTH;
	begin.y = (HEIGHT / 2) - (wall_strip_height / 2);
	if (cub->ray->foundhorzwall == 1)
	{
		offset = (int)floor(cub->ray[idcol].horzwallhitx) % PIXELS;
		if (cub->ray[idcol].israyfacingup == 1)
			txt = cub->img[0];
		else
			txt = cub->img[1];
	}	
	else
	{
		offset = (int)floor(cub->ray[idcol].vertwallhity) % PIXELS;
		if (cub->ray[idcol].israyfacingleft == 1)
			txt = cub->img[2];
		else
			txt = cub->img[3];
	}
	print_rectangle_text(begin, (t_dim){WALL_STRIP_WIDTH, wall_strip_height}, &cub->game, &txt, offset);
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

void	render_rays(t_cub *cub, t_player *player)
{
	t_coord	begin;
	t_coord	end;
	double	rangle;
	int		i;

	begin.y = player->y * PIXELS;
	begin.x = player->x * PIXELS;
	rangle = player->rotationangle - (FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		reinit_ray(&cub->ray[i], rangle);
		dda(cub, &cub->ray[i]);
		cub->ray[i].distance *= cos(rangle - player->rotationangle);
		end.x = begin.x + cos(cub->ray[i].rayangle) * cub->ray[i].distance;
		end.y = begin.y + sin(cub->ray[i].rayangle) * cub->ray[i].distance;
		print_line(begin, end, &cub->minimap);
		my_mlx_pixel_put(&cub->game, 100, 100, RED);
		projection(cub, i);
		rangle += FOV / NUM_RAYS;
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
				render_pixels(PIXELS, &cub->minimap, (t_coord){j, i}, BLACK);
			else if (cub->map[i][j] != ' ')
				render_pixels(PIXELS, &cub->minimap, (t_coord){j, i}, WHITE);
		}
	}
	mlx_clear_window(cub->mlx, cub->win);
	print_square(player->x * PIXELS, player->y * PIXELS, 7, &cub->minimap);
	render_rays(cub, player);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->game.img, 0, 0);
	// mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img,
		// WIDTH - (cub->width_map * PIXELS), 0);
}
