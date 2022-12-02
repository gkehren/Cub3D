/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/02 02:05:34 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_image(t_cub *cub, int n, int i, int j)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img[n].addr,
		j * PIXELS, i * PIXELS);
}

void	render_map(char **map, t_cub *cub, t_player *player)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1')
				render_image(cub, BLACK, i, j);
			else if (map[i][j] == '0')
				render_image(cub, WHITE, i, j);
			else if (map[i][j] == 'N')
				render_image(cub, WHITE, i, j);
		}
	}
	render_image(cub, BLUE, player->x, player->y);
}
