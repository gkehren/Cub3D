/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 23:48:55 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/11 23:50:13 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**copy_second(char **map, char **pmap, int j, int nb_line)
{
	int	n;
	int	i;
	int	len_max;

	n = 0;
	len_max = get_max(pmap);
	while (j < nb_line)
	{
		i = 0;
		map[n] = (char *)malloc(sizeof(char) * len_max + 1);
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

char	**copy(char **map, char **pmap, int rec_index)
{
	int	j;
	int	nb_line;

	j = get_start_map_bis(pmap, rec_index);
	nb_line = j;
	if (j == -1)
		return (free_double_tab((void **)pmap), NULL);
	while (pmap[nb_line])
		nb_line++;
	map = (char **)malloc(sizeof(char *) * (nb_line - j + 1));
	map = copy_second(map, pmap, j, nb_line);
	free_double_tab((void **)pmap);
	return (map);
}
