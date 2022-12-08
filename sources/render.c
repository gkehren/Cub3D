/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/08 12:28:46 by genouf           ###   ########.fr       */
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

void	projection(t_cub *cub, double ray_dist, int idcol)
{
	double	distance_proj_plane;
	double	wall_strip_height;
	t_coord	begin;
	t_coord	begin2;

	distance_proj_plane = (WIDTH / 2) / tan(FOV / 2);
	wall_strip_height = (PIXELS / ray_dist) * distance_proj_plane;
	begin.x = idcol * WALL_STRIP_WIDTH;
	begin.y = (HEIGHT / 2) - (wall_strip_height / 2);
	print_rectangle(begin, (t_dim){WALL_STRIP_WIDTH, wall_strip_height},
		&cub->game, GREEN);
	begin2.x = begin.x;
	begin2.y = 0;
	print_rectangle(begin2, (t_dim){WALL_STRIP_WIDTH, begin.y},
		&cub->game, BLUE);
	begin2.y = begin.y + wall_strip_height;
	print_rectangle(begin2, (t_dim){WALL_STRIP_WIDTH, HEIGHT - begin2.y},
		&cub->game, RED);
}

void	render_rays(t_cub *cub, t_player *player)
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
		dist = dda(cub, &cub->ray[i]) * cos(rangle - player->rotationangle);
		end.x = begin.x + cos(cub->ray[i].rayangle) * dist;
		end.y = begin.y + sin(cub->ray[i].rayangle) * dist;
		print_line(begin, end, &cub->minimap);
		my_mlx_pixel_put(&cub->game, 100, 100, RED);
		projection(cub, dist, i);
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
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img,
		WIDTH - (cub->width_map * PIXELS), 0);
}
