/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:21:27 by genouf            #+#    #+#             */
/*   Updated: 2022/12/12 00:05:08 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	distance(t_coord begin, t_coord end)
{
	t_coord	distance;

	distance.x = end.x - begin.x;
	distance.y = end.y - begin.y;
	return (sqrt(distance.x * distance.x + distance.y * distance.y));
}

/*				OTHERS				*/
int	get_start_map_bis(char **map, int rec_index)
{
	int	j;

	j = rec_index;
	while (map[j])
	{
		if (map[j][0] == ' ' || map[j][0] == '1')
			return (j);
		else if (map[j][0] != '\n')
			return (-1);
		j++;
	}
	return (-1);
}

bool	check_line_rgb(char *str)
{
	int	i;

	i = 2;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ','
			&& str[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}
