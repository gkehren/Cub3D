/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:49:56 by gkehren           #+#    #+#             */
/*   Updated: 2022/12/11 22:56:16 by genouf           ###   ########.fr       */
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

int	strcmp_begin_m(char *str1, char *str2, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_begin_map(t_cub *cub, char **map)
{
	const char	*tab[] = {"NO ", "SO ", "WE ", "EA ", "F ", "C ", NULL};
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (map && tab[j] && map[i])
	{
		if (map[i][0] == '\n')
			i++;
		else
		{
			if (strcmp_begin_m((char *)tab[j], map[i],
					ft_strlen((char *)tab[j])))
				return (1);
			i++;
			j++;
		}
	}
	cub->rec_index = i;
	return (0);
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
