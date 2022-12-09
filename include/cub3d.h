/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:26 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/09 15:47:03 by gkehren          ###   ########.fr       */
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
# include <limits.h>
# include <math.h>
# include <stdbool.h>
#include <X11/keysym.h>

/*=====DEFINE=====*/
# define WIDTH 1920
# define HEIGHT 1080
# define PIXELS 16
# define PI 3.14159265
# define IMG 4

/*=====COLOR'S DEFINE=====*/
# define BLACK 0x5B5767
# define WHITE 0x6C6877
# define BLUE 0x1E90FF
# define GREEN 0x32CD32
# define RED 0xff0000

/*=====RAY'S DEFINE=====*/
# define FOV (60 * (PI / 180))
# define WALL_STRIP_WIDTH 4
# define NUM_RAYS (WIDTH / WALL_STRIP_WIDTH)

/*=====STRUCT=====*/
typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_dimension
{
	int	width;
	int	height;
}	t_dim;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	turn_x;
	double	turn_y;
	double	turndirection;
	double	walkdirection;
	double	rotationangle;
	double	walkspeed;
	double	turnspeed;
}	t_player;

typedef struct s_ray
{
	double	rayangle;
	double	horzwallhitx;
	double	horzwallhity;
	double	vertwallhitx;
	double	vertwallhity;
	double	distance;
	bool	foundhorzwall;
	bool	foundvertwall;
	int		israyfacingup;
	int		israyfacingdown;
	int		israyfacingleft;
	int		israyfacingright;
	int		horzwallhitcontent;
	int		vertwallhitcontent;
}	t_ray;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	char		**map;
	int			width_map;
	int			height_map;
	t_img		*img;
	t_img		minimap;
	t_img		game;
	t_player	player;
	t_ray		*ray;
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	int			rgb_floor[3];
	int			rgb_ceiling[3];
}	t_cub;

/*=====DISPLAY=====*/
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		init_window(t_cub *cub);
int			close_window(t_cub *cub);
void		generate_img(t_cub *cub);
void		render_minimap(t_cub *cub, t_player *player);
int			move_player(int keycode, t_cub *cub);
void		init_rays(t_cub *cub);
void		init_player(t_cub *cub);
/*=====INTERSECTIONS=====*/
double		dda(t_cub *cub, t_ray *ray);
void		where_ray_facing(t_ray *ray);
double		return_ray(t_cub *cub, t_ray *ray);
bool		has_wall_at(t_cub *cub, double x, double y);
/*=================*/

/*=====PARSING=====*/
int			parse_input(int argc, char **argv, t_cub *cub);
char		*get_next_line(int fd);
bool		map_close(char **map);
bool		check_char_map(char **map, t_cub *cub);
int			check_path(char *file);
char		**get_map(char *file);
int			get_max(char **map);
bool		get_texture(t_cub *cub, char **map, int start);
char		*ft_strcpy_texture(char *dst, char *src);
/*=================*/

/*=====PRINT_FORMS=====*/
void		print_cross(int x, int y, t_img *img);
void		print_square(int x, int y, int size, t_img *img);
void		print_line(t_coord begin, t_coord end, t_img *img);
void		print_rectangle(t_coord begin, t_dim dim, t_img *img, int color);
double		distance(t_coord begin, t_coord end);
/*=================*/

/*=====INIT=====*/
void		init_rays(t_cub *cub);
void		reinit_ray(t_ray *ray, double rangle);
/*=================*/

/*=====UTILS=====*/
char		*ft_strcpy(char *dst, char *src);
size_t		ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strchr(char *s, int c);
void		free_double_tab(void **ptr);
double		max(double a, double b);
double		min(double a, double b);
/*===============*/

#endif
