/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:50:36 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/07 14:33:21 by genouf           ###   ########.fr       */
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
		if ((i == (ft_strlen(line) - 1) && line[i] != ' ')
			&& (i == (ft_strlen(line) - 1) && line[i] != '1'))
			return (false);
		if (i > 0 && i < ft_strlen(line))
			if (line[i] == ' ' && (line[i + 1] == '0' || line[i + 1] == '\0'))
				return (false);
		i++;
	}
	return (true);
}

bool	another_one(char **map, int j, int i)
{
	if (map[j][i] == ' ' && (map[j + 1][i] == '0'
		|| map[j + 1][i] == '\0'))
		return (false);
	if (map[j][i] == ' ' && (map[j + 1][i + 1] == '0'
		|| map[j + 1][i + 1] == '\0'))
		return (false);
	if (map[j][i] == ' ' && (map[j - 1][i] == '0'
		|| map[j - 1][i] == '\0'))
		return (false);
	if (map[j][i] == '0' && (map[j + 1][i] == '\0'
		|| map[j + 1][i + 1] == '\0' || map[j + 1][i] == ' '
		|| map[j + 1][i + 1] == ' '))
		return (false);
	if (map[j][i] == '0' && (map[j - 1][i] == '\0'
		|| map[j - 1][i + 1] == '\0' || map[j - 1][i] == ' '
		|| map[j - 1][i + 1] == ' '))
		return (false);
	if (map[j][i] == '0' && (map[j + 1][i - 1] == '\0'
		|| map[j + 1][i - 1] == ' '))
		return (false);
	return (true);
}

bool	check_else(char **map, int j, int i, int nb_line)
{
	while (map[j][i])
	{
		if ((j == 0 && map[j][i] != ' ') && (j == 0 && map[j][i] != '1'))
			return (false);
		if ((j == (nb_line) && map[j][i] != ' ') && (j == (nb_line)
			&& map[j][i] != '1'))
			return (false);
		if (j > 0 && j < nb_line - 1)
			if (another_one(map, j, i) == false)
				return (false);
		i++;
	}
	return (true);
}

bool	map_close(char **map)
{
	int	j;
	int	nb_line;

	j = 0;
	nb_line = 0;
	while (map[nb_line])
		nb_line++;
	while (map[j])
	{
		if (check_line(map[j]) == false)
			return (false);
		if (check_else(map, j, 0, nb_line) == false)
			return (false);
		j++;
	}
	return (true);
}

bool	check_char_map(char **map, t_cub *cub)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] != ' ' && map[j][i] != '1' && map[j][i] != '0'
				&& map[j][i] != 'N' && map[j][i] != 'S' && map[j][i] != 'E'
				&& map[j][i] != 'W' && map[j][i] != '\0')
				return (false);
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E'
				|| map[j][i] == 'W')
			{
				cub->player.x = i;
				cub->player.y = j;
			}
			i++;
		}
		j++;
	}
	return (true);
}
