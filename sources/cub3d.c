/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:45:04 by gkehren           #+#    #+#             */
/*   Updated: 2022/11/24 13:48:14 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_window(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free_double_tab((void **)cub->map);
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
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx_key_hook(cub->win, key_hook, cub);
	mlx_hook(cub->win, 17, 0, close_window, cub);
	mlx_loop(cub->mlx);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		printf("%s\n", map[i++]);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (parse_input(argc, argv, &cub))
		return (0);
	print_map(cub.map);
	return (free_double_tab((void **)cub.map), 0);
	//init_window(&cub);
	//return (close_window(&cub), 0);
}
