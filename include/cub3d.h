/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:26 by gkehren           #+#    #+#             */
/*   Updated: 2022/11/23 17:12:21 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

# define WIDTH 1920
# define HEIGHT 1080
# define PIXELS 32

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	char	**map;
}				t_cub;

/*=====PARSING=====*/
int			parse_input(int argc, char **argv, t_cub *cub);
char		*get_next_line(int fd);
int			map_close(char **map);
/*=================*/

/*=====UTILS=====*/
char		*ft_strcpy(char *dst, char *src);
size_t		ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strchr(char *s, int c);
void		free_double_tab(void **ptr);
/*===============*/

#endif
