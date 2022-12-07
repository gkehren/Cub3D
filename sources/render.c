/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/07 18:43:39 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_image(t_cub *cub, int n, int i, int j)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img[n].img,
		((j * PIXELS) + (WIDTH - (cub->width_map) * PIXELS)), i * PIXELS);
}

void	render_pixels(int size, t_img *img, int y, int x, int color)
{
	int	end_col;
	int	end_line;
	int	i;
	int	j;

	end_line = (x + 1) * size;
	end_col = (y + 1) * size;
	i = y * size;
	while (i < end_col)
	{
		j = x * size;
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
		cub->ray[i].wallhitcontent = 0;
		cub->ray[i].wallhitx = 0;
		cub->ray[i].wallhity = 0;
		cub->ray[i].washitvertical = 0;
		cub->ray[i].foundhorzWall = false;
		i++;
	}
}

void	render_rays(t_cub *cub, t_player *player, t_img *img)
{
	t_coord	begin;
	t_coord end;
	double	rangle;
	int		i;

	begin.y = player->y * PIXELS;
	begin.x = player->x * PIXELS;
	(void)cub;
	//cub->ray[0].distance = 0;
	//cub->ray[0].israyfacingdown = 0;
	//cub->ray[0].israyfacingleft = 0;
	//cub->ray[0].israyfacingright = 0;
	//cub->ray[0].israyfacingup = 0;
	//cub->ray[0].wallhitcontent = 0;
	//cub->ray[0].wallhitx = 0;
	//cub->ray[0].wallhity = 0;
	//cub->ray[0].rayangle += FOV_ANGLE / NUM_RAYS;
	//cub->ray[0].foundhorzWall = false;
	//dda(cub, &cub->ray[0]);
	//end.x = begin.x + cos(player->rotationangle) * 60;
	//end.y = begin.y + sin(player->rotationangle) * 60;
	//print_line(begin, end, img);
	rangle = player->rotationangle - (FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		end.x = begin.x + cos(rangle) * 100;
		end.y = begin.y + sin(rangle) * 100;
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
				render_pixels(PIXELS, &cub->minimap, i, j, BLACK);
			else if (cub->map[i][j] != ' ')
				render_pixels(PIXELS, &cub->minimap, i, j, WHITE);
		}
	}
	print_square(player->x * PIXELS, player->y * PIXELS, 7, &cub->minimap);
	render_rays(cub ,player, &cub->minimap);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img,
		WIDTH - (cub->width_map * PIXELS), 0);
}
