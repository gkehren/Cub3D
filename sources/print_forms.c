/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_forms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:56:46 by genouf            #+#    #+#             */
/*   Updated: 2022/12/12 22:25:20 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_cross(int x, int y, t_img *img)
{
	int	begin;
	int	aled;

	begin = x - 3;
	aled = begin + 7;
	while (begin < aled)
	{
		my_mlx_pixel_put(img, y, begin, BLUE);
		begin++;
	}
	begin = y - 3;
	aled = begin + 7;
	while (begin < aled)
	{
		my_mlx_pixel_put(img, begin, x, BLUE);
		begin++;
	}
}

void	print_square(int x, int y, int size, t_img *img)
{
	int	end_col;
	int	end_line;
	int	tmp;

	end_col = x + (size / 2);
	end_line = y + (size / 2);
	x -= (size / 2);
	y -= (size / 2);
	while (x < end_col)
	{
		tmp = y;
		while (tmp < end_line)
		{
			my_mlx_pixel_put(img, x, tmp, BLUE);
			tmp++;
		}
		x++;
	}
}

void	print_line(t_coord begin, t_coord end, t_img *img)
{
	t_coord	distance;
	double	max_v;
	int		i;

	distance.x = end.x - begin.x;
	distance.y = end.y - begin.y;
	max_v = max(fabs(distance.x), fabs(distance.y));
	i = 1;
	while (i < max_v + 1)
	{
		my_mlx_pixel_put(img, (int)(begin.x + (distance.x * i / max_v)),
			(int)(begin.y + (distance.y * i / max_v)), 0xff0000);
		i++;
	}
}

void	print_rectangle(t_coord begin, t_dim dim, t_img *img, int color)
{
	t_coord	end;
	double	x;
	double	y;

	end.x = begin.x + dim.width;
	end.y = begin.y + dim.height;
	y = begin.y;
	while (y < end.y)
	{
		x = begin.x;
		while (x < end.x)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	print_rectangle_text(t_coord begin, t_dim dim, t_proj *proj)
{
	t_coord	end;
	double	x;
	double	y;
	double	x_txt;
	double	y_txt;

	x_txt = proj->offset / PIXELS * proj->txt.width;
	end.x = begin.x + dim.width;
	end.y = begin.y + dim.height;
	y = begin.y - 1;
	while (++y < end.y)
	{
		x = begin.x;
		if ((y >= 0 && y < HEIGHT) && (x >= 0 && x < WIDTH))
		{
			y_txt = (y - begin.y) / dim.height * proj->txt.height;
			while (x < end.x)
			{
				my_mlx_pixel_put(proj->screen, x, y,
					my_mlx_pixel_get(&proj->txt,
						(int)floor(x_txt), (int)floor(y_txt)));
				x++;
			}
		}
	}
}
