/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/05 19:20:16 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_image(t_cub *cub, int n, int i, int j)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img[n].img,
		((j * PIXELS) + (WIDTH - (cub->width_map) * PIXELS)), i * PIXELS);
}

void	render_pixels(int size, t_img *img, int x, int y, int color)
{
	int	end_col;
	int	end_line;
	int	i;
	int	j;

	end_line = (y + 1) * size;
	end_col = (x + 1) * size;
	i = x * size;
	while (i < end_col)
	{
		j = y * size;
		while (j < end_line)
		{
			my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

void	render_player(t_cub *cub, t_player *player, t_player *bplayer)
{
	render_pixels(PIXELS, &cub->minimap,(int)bplayer->x, (int)bplayer->y, 0x6C6877);
	render_pixels(PIXELS, &cub->minimap,(int)player->x, (int)player->y, 0x1E90FF);
}

void	render_minimap(t_cub *cub, t_player *player, t_player *bplayer, int rr)
{
	int	i;
	int	j;

	i = -1;
	cub->minimap.addr = mlx_get_data_addr(cub->minimap.img, &cub->minimap.bits_per_pixel, &cub->minimap.line_length, &cub->minimap.endian);
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == '1' && rr)
				render_pixels(PIXELS, &cub->minimap, i, j, 0x5B5767);
			else if (cub->map[i][j] != ' ' && rr)
				render_pixels(PIXELS, &cub->minimap, i, j, 0x6C6877);
		}
	}
	render_player(cub, player, bplayer);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img, WIDTH - (cub->width_map * PIXELS), 0);
}

