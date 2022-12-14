/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:44:26 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/11 23:58:35 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_max(char **map)
{
	int	j;
	int	max;

	j = get_start_map(map);
	max = 0;
	while (map[j])
	{
		if ((int)ft_strlen(map[j]) > max)
			max = ft_strlen(map[j]);
		j++;
	}
	return (max);
}

int	ft_atoi_rgb(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + str[i] - 48;
		i++;
	}
	return (nbr);
}

bool	get_rgb(char	*map, int *rgb)
{
	int	i;

	i = 1;
	if (check_line_rgb(map) == false)
		return (false);
	rgb[0] = ft_atoi_rgb(map + i);
	while (map[i] && map[i] != ',')
		i++;
	i++;
	rgb[1] = ft_atoi_rgb(map + i);
	while (map[i] && map[i] != ',')
		i++;
	i++;
	rgb[2] = ft_atoi_rgb(map + i);
	if (rgb[0] > 255 || rgb[0] < 0 || rgb[1] > 255 || rgb[1] < 0
		|| rgb[2] > 255 || rgb[2] < 0)
		return (false);
	return (true);
}

bool	get_texture_rgb(t_cub *cub, char **map, int j, int start)
{
	while (j < start && map[j][0] == '\n')
		j++;
	if (get_rgb(map[j], cub->rgb_floor) == false)
		return (false);
	j++;
	while (j < start && map[j][0] == '\n')
		j++;
	if (get_rgb(map[j], cub->rgb_ceiling) == false)
		return (false);
	return (true);
}

bool	get_texture(t_cub *cub, char **map, int start, int j)
{
	if (check_begin_map(cub, map))
		return (free_double_tab((void **)map), false);
	while (j < start && map[j][0] == '\n')
		j++;
	cub->path_no = ft_strcpy_texture(cub->path_no, map[j]);
	j++;
	while (j < start && map[j][0] == '\n')
		j++;
	cub->path_so = ft_strcpy_texture(cub->path_we, map[j]);
	j++;
	while (j < start && map[j][0] == '\n')
		j++;
	cub->path_we = ft_strcpy_texture(cub->path_we, map[j]);
	j++;
	while (j < start && map[j][0] == '\n')
		j++;
	cub->path_ea = ft_strcpy_texture(cub->path_ea, map[j]);
	j++;
	if (!cub->path_no || !cub->path_so || !cub->path_we || !cub->path_ea)
		return (free_double_tab((void **)map), free_path(cub), false);
	if (get_texture_rgb(cub, map, j, start) == false)
		return (free_double_tab((void **)map), free_path(cub), false);
	return (true);
}
