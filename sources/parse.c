/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:52:06 by gkehren           #+#    #+#             */
/*   Updated: 2022/11/23 23:21:08 by gkehren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_number_line(int fd)
{
	int		line;
	char	*tmp;

	tmp = get_next_line(fd);
	free(tmp);
	line = 0;
	while (tmp != NULL)
	{
		tmp = get_next_line(fd);
		free(tmp);
		line++;
	}
	return (line);
}

char	**get_map(char *file)
{
	char	**map;
	int		line;
	int		i;
	int		fd;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_number_line(fd) + 1;
	map = (char **)malloc(sizeof(char *) * line);
	close(fd);
	fd = open(file, O_RDONLY);
	while (i < line)
		map[i++] = get_next_line(fd);
	close(fd);
	return (map);
}

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

char	**copy(char **map, char **pmap)
{
	int	i;
	int	j;
	int	nb_line;

	nb_line = 0;
	while (pmap[nb_line])
		nb_line++;
	map = (char **)malloc(sizeof(char *) * (nb_line + 1));
	j = 0;
	while (j < nb_line)
	{
		i = 0;
		map[j] = (char *)malloc(sizeof(char) * ft_strlen(pmap[j]));
		while (pmap[j][i] != '\n' && pmap[j][i])
		{
			map[j][i] = pmap[j][i];
			i++;
		}
		map[j][i] = '\0';
		j++;
	}
	map[j] = NULL;
	free_double_tab((void **)pmap);
	return (map);
}

int	parse_input(int argc, char **argv, t_cub *cub)
{
	char	**pmap;

	if (argc != 2)
		return (printf("Please give a map path\n"), 1);
	if (check_path(argv[1]))
		return (printf("given map is invalid\n"), 1);
	pmap = get_map(argv[1]);
	if (!pmap)
		return (printf("Error: can't open file\n"), 1);
	cub->map = copy(cub->map, pmap);
	if (map_close(cub->map) == false)
		return (printf("Error: map is not close\n"), free_double_tab((void **)cub->map), 1);
	return (0);
}
