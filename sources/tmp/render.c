/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/06 20:13:30 by genouf           ###   ########.fr       */
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

void	print_cross(int x, int y, t_img *img)
{
	int	begin;
	int	aled;

	begin = x - 3;
	aled = begin + 7;
	while (begin < aled)
	{
		my_mlx_pixel_put(img, y, begin, BLUE);
		begin++;
	}
	begin = y - 3;
	aled = begin + 7;
	while (begin < aled)
	{
		my_mlx_pixel_put(img, begin, x, BLUE);
		begin++;
	}
}

void	print_square(int x, int y, int size, t_img *img)
{
	int	end_col;
	int	end_line;
	int	tmp;

	end_col = x + (size / 2);
	end_line = y + (size / 2);
	x -= (size / 2);
	y -= (size / 2);
	while (x < end_col)
	{
		tmp = y;
		while (tmp < end_line)
		{
			my_mlx_pixel_put(img, tmp, x, BLUE);
			tmp++;
		}
		x++;
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
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img,
		WIDTH - (cub->width_map * PIXELS), 0);
}
