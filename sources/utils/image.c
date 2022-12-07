/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:29:34 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/07 12:54:53 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	
	if (x > img->width || y > img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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
	static char	*path[IMG] = {
		"./assets/black.xpm",
		"./assets/white.xpm",
		"./assets/blue.xpm",
		"./assets/green.xpm"};

	i = 0;
	cub->img = (t_img *)malloc(sizeof(t_img) * IMG);
	while (i < IMG)
	{
		cub->img[i].img = get_image(cub, path[i]);
		i++;
	}
}
