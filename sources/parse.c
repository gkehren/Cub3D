/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:06 by gkehren           #+#    #+#             */
/*   Updated: 2022/11/26 14:51:04 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

char	**copy_second(char **map, char **pmap, int j, int nb_line)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (j < nb_line)
	{
		i = 0;
		map[n] = (char *)malloc(sizeof(char) * ft_strlen(pmap[j]));
		while (pmap[j][i] != '\n' && pmap[j][i])
		{
			map[n][i] = pmap[j][i];
			i++;
		}
		map[n][i] = '\0';
		j++;
		n++;
	}
	map[n] = NULL;
	return (map);
}

char	**copy(char **map, char **pmap)
{
	int	j;
	int	nb_line;

	j = get_start_map(pmap);
	nb_line = j;
	if (j == -1)
		return (NULL);
	while (pmap[nb_line])
		nb_line++;
	map = (char **)malloc(sizeof(char *) * (nb_line - j + 1));
	map = copy_second(map, pmap, j, nb_line);
	free_double_tab((void **)pmap);
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
	cub->map = copy(cub->map, pmap);
	if (!cub->map)
		return (printf("Error: map not found\n"), 1);
	if (map_close(cub->map) == false)
		return (printf("Error: map is not close\n"),
			free_double_tab((void **)cub->map), 1);
	if (check_char_map(cub->map) == false)
		return (printf("Error: map contains invalid characters\n"), 1);
	return (0);
}
