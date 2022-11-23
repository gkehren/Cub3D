/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:50:36 by gkehren           #+#    #+#             */
/*   Updated: 2022/11/24 00:11:07 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	check_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if ((i == 0 && line[i] != ' ') && (i == 0 && line[i] != '1'))
			return (false);
		if ((i == (ft_strlen(line) - 1) && line[i] != ' ') && (i == (ft_strlen(line) - 1) && line[i] != '1'))
			return (false);
		if (i > 0 && i < ft_strlen(line))
			if (line[i] == ' ' && (line[i + 1] == '0' || line[i + 1] == '\0'))
				return (false);
		i++;
	}
	return (true);
}

bool	map_close(char **map)
{
	int	i;
	int	j;
	int	nb_line;

	i = 0;
	j = 0;
	nb_line = 0;
	while (map[nb_line++]);
	while (map[j])
	{
		if (j == 0)
			if (check_line(map[j]) == false)
				return (false);
		if (j == nb_line - 1)
			if (check_line(map[j]) == false)
				return (false);
		if (check_line(map[j]) == false)
			return (false);
		j++;
	}
	return (true);
}
