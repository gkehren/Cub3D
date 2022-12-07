/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:21:27 by genouf            #+#    #+#             */
/*   Updated: 2022/12/07 17:26:45 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	max(double a, double b)
{
	if (a == b)
		return (b);
	if (a > b)
		return (a);
	else
		return (b);	
}

double	min(double a, double b)
{
	if (a == b)
		return (b);
	if (a < b)
		return (a);
	else
		return (b);	
}