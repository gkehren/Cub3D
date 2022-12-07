/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/07 13:00:09 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	render_rays(t_player *player, t_img *img)
{
	t_coord	begin;
	t_coord end;

	begin.y = player->x * PIXELS;
	begin.x = player->y * PIXELS;
	printf("turn x : %f\n", player->turn_x);
	printf("turn y : %f\n", player->turn_y);
	end.x = begin.x + cos(player->turn_x) * 400;
	end.y = begin.y + sin(player->turn_y) * 400;
	// begin.x = 0;
	// begin.y = 0;
	// end.x = 0;
	// end.y = 100;
	printf("begin x : %f\n", begin.x);
	printf("begin y : %f\n", begin.y);
	printf("cos : %f\n", cos(player->turn_x) * 20);
	printf("sin : %f\n", sin(player->turn_y) * 20);
	printf("end x : %f\n", end.x);
	printf("end y : %f\n", end.y);
	// (void)img;
	// (void)player;
	print_line(begin, end, img);
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
	render_rays(player, &cub->minimap);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img,
		WIDTH - (cub->width_map * PIXELS), 0);
}