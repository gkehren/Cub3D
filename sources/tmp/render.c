/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:34:40 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/05 16:42:12 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_image(t_cub *cub, int n, int i, int j)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img[n].addr,
		((j * PIXELS) + (WIDTH - (cub->len_map) * PIXELS)), i * PIXELS);
}

void	render_player(t_cub *cub, t_player *player, t_player *bplayer)
{
	render_image(cub, WHITE, bplayer->x, bplayer->y);
	render_image(cub, BLUE, player->x, player->y);
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
				render_image(cub, BLACK, i, j);
			else if (cub->map[i][j] != ' ' && rr)
				render_image(cub, WHITE, i, j);
		}
	}
	render_player(cub, player, bplayer);
}
