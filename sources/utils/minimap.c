/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:24:35 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/11 23:40:13 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

unsigned int	get_map_color(t_cub *cub, int x, int y)
{
	if (x < 0 || y < 0 || x >= cub->width_map || y >= cub->height_map)
		return (BLACK);
	else if (cub->map[y][x] == '1')
		return (BLACK);
	else if (cub->map[y][x] == ' ')
		return (BLACK);
	else
		return (WHITE);
}

void	render_minimap(t_cub *cub, t_player *player)
{
	t_coord			begin;
	unsigned int	color;
	int				i;
	int				j;

	i = 0;
	begin.y = player->y - 10;
	while (i < 20)
	{
		j = 0;
		begin.x = player->x - 10;
		while (j < 20)
		{
			color = get_map_color(cub, (int)floor(begin.x),
					(int)floor(begin.y));
			render_pixels(MAP, &cub->minimap, (t_coord){j, i}, color);
			j++;
			begin.x++;
		}
		begin.y++;
		i++;
	}
	print_square(10.5 * MAP, 10.5 * MAP, 8, &cub->minimap);
}

void	full_render_minimap(t_cub *cub, t_player *player)
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
			else
				render_pixels(MAP, &cub->minimap, (t_coord){j, i}, BLACK);
		}
	}
	print_square(player->x * MAP, player->y * MAP, 8, &cub->minimap);
}
