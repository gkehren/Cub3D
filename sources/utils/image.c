/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:29:34 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/08 16:45:44 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x > img->width || y > img->height || x < 0 || y < 0)
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

void	free_img(t_cub *cub)
{
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

void	generate_img(t_cub *cub)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	cub->img = (t_img *)malloc(sizeof(t_img) * IMG);
	cub->img[0].img = get_image(cub, cub->path_no);
	cub->img[1].img = get_image(cub, cub->path_so);
	cub->img[2].img = get_image(cub, cub->path_we);
	cub->img[3].img = get_image(cub, cub->path_ea);
	while (i < IMG)
	{
		if (cub->img[i].img == NULL)
		{
			printf("Error: the %d given texture is invalid\n", i + 1);
			while (n < IMG)
			{
				if (cub->img[n].img != NULL)
					mlx_destroy_image(cub->mlx, cub->img[n].img);
				n++;
			}
			free_img(cub);
		}
		i++;
	}
}
