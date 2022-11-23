/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:45:04 by gkehren           #+#    #+#             */
/*   Updated: 2022/11/23 16:17:58 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_window(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == 65307)
		close_window(cub);
	return (0);
}

void	init_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, 1920, 1080, "Cub3D");
	mlx_key_hook(cub->win, key_hook, cub);
	mlx_hook(cub->win, 17, 0, close_window, cub);
	mlx_loop(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (parse_input(argc, argv))
		return (0);
	init_window(&cub);
	return (close_window(&cub), 0);
}
