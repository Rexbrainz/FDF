/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_coordinates.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:40:08 by sudaniel          #+#    #+#             */
/*   Updated: 2024/11/23 18:05:02 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	three_d(int *x, int *y, int z)
{
	int	temp;

	temp = *x;
	*x = (temp - *y) * cos(0.8);
	*y = (temp + *y) * sin(0.523599) - z;
}

static void	pre_transform_points(t_map *map_info, t_point **transformed_points)
{
	int	y;
	int	x;
	int	tx;
	int	ty;
	int	tz;

	y = 0;
	while (y < map_info->height)
	{
		x = 0;
		while (x < map_info->width)
		{
			tx = x * 20;
			ty = y * 20;
			tz = map_info->points[y][x];
			three_d(&tx, &ty, tz);
			transformed_points[y][x].x = tx + WIDTH / 2;
			transformed_points[y][x].y = ty + HEIGHT / 2;
			x++;
		}
		y++;
	}
}

static t_bline_args	init_args(int x, int y, int x1, int y1)
{
	t_bline_args	args;

	args.x = x;
	args.y = y;
	args.x1 = x1;
	args.y1 = y1;
	return (args);
}

static void	obtain_points_and_draw(t_map *map_info,
		t_point **transformed_points)
{
	int				x;
	int				y;
	t_bline_args	args;

	y = 0;
	while (y < map_info->height)
	{
		x = 0;
		while (x < map_info->width)
		{
			if (x < map_info->width - 1)
			{
				args = init_args(x, y, x + 1, y);
				initialize_bline(args, map_info, transformed_points);
			}
			if (y < map_info->height - 1)
			{
				args = init_args(x, y, x, y + 1);
				initialize_bline(args, map_info, transformed_points);
			}
			x++;
		}
		y++;
	}
}

void	connect_coordinates(t_map *map_info)
{
	t_point	**transformed_points;
	int		i;

	transformed_points = (t_point **) malloc(sizeof(t_point *)
			* map_info->height);
	if (!transformed_points)
		error("Error: Malloc failed at connect_coordinates.\n");
	i = 0;
	while (i < map_info->height)
	{
		transformed_points[i] = malloc(sizeof(t_point) * map_info->width);
		if (!transformed_points[i++])
		{
			while (transformed_points[i--])
				free(transformed_points[i]);
			free(transformed_points);
			error("Error: Malloc failed at connect_coordinates.\n");
		}
	}
	pre_transform_points(map_info, transformed_points);
	obtain_points_and_draw(map_info, transformed_points);
	i = 0;
	while (i < map_info->height)
		free(transformed_points[i++]);
	free(transformed_points);
}
