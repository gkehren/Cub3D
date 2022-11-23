/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:06 by gkehren           #+#    #+#             */
/*   Updated: 2022/11/23 16:02:44 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_path(char *file)
{
	size_t	i;

	i = 0;
	while (file[i])
		i++;
	if (i < 4)
		return (1);
	else if (file[i - 4] == '.' && file[i - 3] == 'c'
		&& file[i - 2] == 'u' && file[i - 1] == 'b')
		return (0);
	return (1);
}

int	parse_input(int argc, char **argv)
{
	if (argc != 2)
		return (printf("Please give a map path\n"), 1);
	if (check_path(argv[1]))
		return (printf("given map is invalid\n"), 1);
	return (0);
}
