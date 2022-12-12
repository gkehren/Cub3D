/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:06 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/12 14:30:31 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_start_map(char **map)
{
	int	j;

	j = 0;
	while (map[j])
	{
		if (map[j][0] == ' ' || map[j][0] == '1')
			return (j);
		j++;
	}
	return (-1);
}

void	len_map(t_cub *cub)
{
	int	j;
	int	max;

	j = 0;
	max = 0;
	while (cub->map[j])
	{
		if ((int)ft_strlen(cub->map[j]) > max)
			max = ft_strlen(cub->map[j]);
		j++;
	}
	cub->width_map = max;
	while (cub->map[j])
		j++;
	cub->height_map = j;
}

char	**replace_map(char **map, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->height_map && map[i])
	{
		j = 0;
		while (j < cub->width_map && map[j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		j = ft_strlen(map[i]);
		while (j < cub->width_map)
		{
			map[i][j] = '1';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	return (map);
}

int	parse_input(int argc, char **argv, t_cub *cub)
{
	char	**pmap;

	if (argc != 2)
		return (printf("Please give a map path\n"), 1);
	if (check_path(argv[1]))
		return (printf("given map is invalid\n"), 1);
	pmap = get_map(argv[1]);
	if (!pmap)
		return (printf("Error: can't open file\n"), 1);
	if (get_texture(cub, pmap, get_start_map(pmap), 0) == false)
		return (printf("Error: texture is invalid\n"), 1);
	cub->map = copy(cub->map, pmap, cub->rec_index);
	if (!cub->map)
		return (free_path(cub), printf("Error: map not found\n"), 1);
	if (map_close(cub) == false)
		return (printf("Error: map is not close\n"),
			free_double_tab((void **)cub->map), 1);
	if (check_char_map(cub->map, cub) == false)
		return (free_double_tab((void **)cub->map), free_path(cub),
			printf("Error: map contains invalid characters\n"), 1);
	len_map(cub);
	cub->map = replace_map(cub->map, cub);
	return (0);
}
