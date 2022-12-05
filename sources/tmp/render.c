/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/05 12:28:09 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_image(t_cub *cub, int n, int i, int j)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img[n].addr,
		j * PIXELS, i * PIXELS);
}

void	render_minimap(t_cub *cub, t_player *player, t_player *bplayer, int rr)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == '1' && rr)
				mlx_put_image_to_window(cub->mlx, cub->win, cub->img[BLACK].addr,
		j * PIXELS, i * PIXELS);
			else if (cub->map[i][j] != ' ' && rr)
				mlx_put_image_to_window(cub->mlx, cub->win, cub->img[WHITE].addr,
		j * PIXELS, i * PIXELS);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img[WHITE].addr,
		bplayer->y * PIXELS, bplayer->x * PIXELS);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img[BLUE].addr,
		player->y * PIXELS, player->x * PIXELS);
}
