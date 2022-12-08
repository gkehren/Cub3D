/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:34:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/08 11:27:34 by genouf           ###   ########.fr       */
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
	cub->game.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->game.width = WIDTH;
	cub->game.height = HEIGHT;
	cub->minimap.img = mlx_new_image(cub->mlx,
			cub->width_map * PIXELS, cub->height_map * PIXELS);
	cub->minimap.width = cub->width_map * PIXELS;
	cub->minimap.height = cub->height_map * PIXELS;
	cub->minimap.addr = mlx_get_data_addr(cub->minimap.img,
			&cub->minimap.bits_per_pixel, &cub->minimap.line_length,
			&cub->minimap.endian);
	cub->game.addr = mlx_get_data_addr(cub->game.img,
			&cub->game.bits_per_pixel, &cub->game.line_length,
			&cub->game.endian);
	render_minimap(cub, &cub->player);
	mlx_hook(cub->win, 2, 1L << 0, move_player, cub);
	mlx_hook(cub->win, 17, 0, close_window, cub);
	mlx_loop(cub->mlx);
}
