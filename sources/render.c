/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/08 00:36:04 by gkehren          ###   ########.fr       */
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
	ray->israyfacingdown = 0;
	ray->israyfacingleft = 0;
	ray->israyfacingright = 0;
	ray->israyfacingup = 0;
	ray->horzwallhitx = 0;
	ray->horzwallhity = 0;
	ray->vertwallhitx = 0;
	ray->vertwallhity = 0;
	ray->rayangle = rangle;
}

void	render_rays(t_cub *cub, t_player *player, t_img *img)
{
	t_coord	begin;
	t_coord	end;
	double	rangle;
	int		i;
	double	dist;

	begin.y = player->y * PIXELS;
	begin.x = player->x * PIXELS;
	rangle = player->rotationangle - (FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		reinit_ray(&cub->ray[i], rangle);
		dist = dda(cub, &cub->ray[i]);
		end.x = begin.x + cos(cub->ray[i].rayangle) * dist;
		end.y = begin.y + sin(cub->ray[i].rayangle) * dist;
		print_line(begin, end, img);
		rangle += FOV / NUM_RAYS;
		i++;
	}
}

void	render_minimap(t_cub *cub, t_player *player)
{
	int	i;
	int	j;

	i = -1;
	cub->minimap.addr = mlx_get_data_addr(cub->minimap.img,
			&cub->minimap.bits_per_pixel, &cub->minimap.line_length,
			&cub->minimap.endian);
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
	print_square(player->x * PIXELS, player->y * PIXELS, 7, &cub->minimap);
	render_rays(cub, player, &cub->minimap);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img,
		WIDTH - (cub->width_map * PIXELS), 0);
}
