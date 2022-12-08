/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:21:27 by genouf            #+#    #+#             */
/*   Updated: 2022/12/08 16:37:51 by gkehren          ###   ########.fr       */
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
