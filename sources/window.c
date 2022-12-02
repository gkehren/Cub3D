/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:34:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/02 02:05:50 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_window(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < IMG)
		mlx_destroy_image(cub->mlx, cub->img[i++].addr);
	free(cub->img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub->path_no);
	free(cub->path_so);
	free(cub->path_we);
	free(cub->path_ea);
	free_double_tab((void **)cub->map);
	exit(0);
}

void	init_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3D");
	generate_img(cub);
	render_map(cub->map, cub, &cub->player);
	mlx_key_hook(cub->win, move_player, cub);
	mlx_hook(cub->win, 17, 0, close_window, cub);
	mlx_loop(cub->mlx);
}
