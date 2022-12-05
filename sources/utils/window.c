/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:34:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/05 18:40:29 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	close_window(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < IMG)
		mlx_destroy_image(cub->mlx, cub->img[i++].img);
	mlx_destroy_image(cub->mlx, cub->minimap.img);
	free(cub->img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub->path_no);
	free(cub->path_so);
	free(cub->path_we);
	free(cub->path_ea);
	free(cub->ray);
	free_double_tab((void **)cub->map);
	exit(0);
}

void	init_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3D");
	generate_img(cub);
	init_player(cub);
	init_rays(cub);
	cub->minimap.img = mlx_new_image(cub->mlx, cub->width_map * PIXELS, cub->height_map * PIXELS);
	render_minimap(cub, &cub->player, &cub->player, 1);
	mlx_hook(cub->win, 2, 1L << 0, move_player, cub);
	mlx_hook(cub->win, 17, 0, close_window, cub);
	mlx_loop(cub->mlx);
}
