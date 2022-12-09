/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:29:34 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/09 15:47:03 by genouf           ###   ########.fr       */
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

unsigned int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	*get_image(t_cub *cub, char *path, int i)
{
	void	*img;

	img = mlx_xpm_file_to_image(cub->mlx, path, &cub->img[i].width,
			&cub->img[i].height);
	if (img)
		cub->img[i].addr = mlx_get_data_addr(img, &cub->img[i].bits_per_pixel,
				&cub->img[i].line_length, &cub->img[i].endian);
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
	cub->img[0].img = get_image(cub, cub->path_no, 0);
	cub->img[1].img = get_image(cub, cub->path_so, 1);
	cub->img[2].img = get_image(cub, cub->path_we, 2);
	cub->img[3].img = get_image(cub, cub->path_ea, 3);
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
