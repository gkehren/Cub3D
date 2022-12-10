/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:45:04 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/10 12:39:19 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	cub.fov = (60 * (PI / 180));
	cub.num_rays = WIDTH / WALL_STRIP_WIDTH;
	if (parse_input(argc, argv, &cub))
		return (0);
	init_window(&cub);
	return (close_window(&cub), 0);
}
