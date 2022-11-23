/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:26 by gkehren           #+#    #+#             */
/*   Updated: 2022/11/23 16:04:53 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_cub
{
	void	*mlx;
	void	*win;
}				t_cub;

/*=====PARSING=====*/
int	parse_input(int argc, char **argv);

#endif
