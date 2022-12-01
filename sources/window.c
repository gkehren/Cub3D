/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:34:15 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/01 22:48:03 by gkehren          ###   ########.fr       */
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

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == 65307)
		close_window(cub);
	return (0);
}

void	render_image(t_cub *cub, int n, int i, int j)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img[n].addr,
		j * PIXELS, i * PIXELS);
}

void	render_map(char **map, t_cub *cub, int rr)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1' && rr)
				render_image(cub, BLACK, i, j);
			else if (map[i][j] == '0' && rr)
				render_image(cub, WHITE, i, j);
			else if (map[i][j] == 'N' && rr)
				render_image(cub, BLUE, i, j);
		}
	}
}

void	init_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3D");
	generate_img(cub);
	mlx_key_hook(cub->win, key_hook, cub);
	render_map(cub->map, cub, 1);
	mlx_hook(cub->win, 17, 0, close_window, cub);
	mlx_loop(cub->mlx);
}
