/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:29:34 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/01 22:47:40 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	*get_image(t_cub *cub, char *path)
{
	int		img_w;
	int		img_h;
	void	*img;

	img = mlx_xpm_file_to_image(cub->mlx, path, &img_w, &img_h);
	return (img);
}

void	generate_img(t_cub *cub)
{
	int			i;
	static char	*path[3] = {
		"./assets/black.xpm",
		"./assets/white.xpm",
		"./assets/blue.xpm"};

	i = 0;
	cub->img = (t_img *)malloc(sizeof(t_img) * 3);
	while (i < 3)
	{
		cub->img[i].addr = get_image(cub, path[i]);
		i++;
	}
}
