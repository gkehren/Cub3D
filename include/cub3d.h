/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:26 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/01 22:47:28 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*=====INCLUDE=====*/
# include "../minilibx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

/*=====DEFINE=====*/
# define WIDTH 1920
# define HEIGHT 1080
# define PIXELS 32
# define IMG 3
# define BLACK 0
# define WHITE 1
# define BLUE 2

/*=====STRUCT=====*/
typedef struct img
{
	void	*addr;
}	t_img;

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	char	**map;
	t_img	*img;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	int		rgb_floor[3];
	int		rgb_ceiling[3];
}				t_cub;

/*=====MLX=====*/
void		init_window(t_cub *cub);
int			close_window(t_cub *cub);
void		generate_img(t_cub *cub);
/*=================*/

/*=====PARSING=====*/
int			parse_input(int argc, char **argv, t_cub *cub);
char		*get_next_line(int fd);
bool		map_close(char **map);
bool		check_char_map(char **map);
int			check_path(char *file);
char		**get_map(char *file);
bool		get_texture(t_cub *cub, char **map, int start);
char		*ft_strcpy_texture(char *dst, char *src);
/*=================*/

/*=====UTILS=====*/
char		*ft_strcpy(char *dst, char *src);
size_t		ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strchr(char *s, int c);
void		free_double_tab(void **ptr);
/*===============*/

#endif
