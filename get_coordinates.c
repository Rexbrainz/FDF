/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 06:49:13 by sudaniel          #+#    #+#             */
/*   Updated: 2024/11/18 18:16:20 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_map_dimension(char	*map, t_map *map_info)
{
	char	*line;
	int		fd;
	char	**points;

	map_info->height = 0;
	map_info->width = 0;
	fd = open(map, O_RDONLY, 0);
	if (fd < 0)
		error("Error: File cannot be opened at get_map_height.\n");
	line = get_next_line(fd);
	if (!line || !(*line >= '0' && *line <= '9'))
		error("Error: Invalid file content.\n");
	points = ft_split(line, ' ');
	if (!points)
		error("Error: Memory allocation failed at get_map_dimension.\n");
	while (points[map_info->width])
		map_info->width++;
	while (line)
	{
		map_info->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	allocate_memory(t_map *map_info)
{
	int	index;

	map_info->points = (int **) malloc(sizeof(int *) * map_info->height);
	if (!map_info->points)
		error("Error: Memory failed.\n");
	index = 0;
	while (index <= map_info->height)
	{
		map_info->points[index] = (int *) malloc(sizeof(int) * map_info->width);
		if (!map_info->points[index])
		{
			while (index--)
				free(map_info->points[index]);
			free(map_info->points);
			error("Error: Memory failed.\n");
		}
		index++;
	}
	map_info->points[index] = NULL;
}

static void	get_map_points(char *line, t_map *map_info)
{
	char		**char_points;
	int			j;
	static int	i;

	char_points = ft_split(line, ' ');
	j = 0;
	while (j < map_info->width)
	{
		map_info->points[i][j] = ft_atoi(char_points[j]);
		free(char_points[j]);
		j++;
	}
	i++;
	free(line);
	free(char_points);
}

void	get_map_details(char *map, t_map *map_info)
{
	int		fd;
	char	*line;
	int		i;

	get_map_dimension(map, map_info);
	if (map_info->height == -1 || map_info->width == -1)
		error("Error: File is empty.\n");
	allocate_memory(map_info);
	fd = open(map, O_RDONLY, 0);
	if (fd < 0)
		error("Error: File cannot be opened at get_map_details.\n");
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line)
			get_map_points(line, map_info);
		else
			break ;
	}
	close(fd);
}
