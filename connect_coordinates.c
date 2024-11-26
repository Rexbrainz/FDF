/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_coordinates.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:40:08 by sudaniel          #+#    #+#             */
/*   Updated: 2024/11/26 12:12:37 by sudaniel         ###   ########.fr       */
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
	t_scale	scale;
	int		y;
	int		x;

	scale.scale_f = get_min(WIDTH, HEIGHT, map_info->width, map_info->height);
	scale.center_x = WIDTH / 2 - (map_info->width / 2) * scale.scale_f;
	scale.center_y = HEIGHT / 2 - (map_info->height / 2) * scale.scale_f;
	if (map_info->width >= 50)
		scale.center_x += 400;
	y = 0;
	while (y < map_info->height)
	{
		x = 0;
		while (x < map_info->width)
		{
			scale.tx = x * scale.scale_f;
			scale.ty = y * scale.scale_f;
			scale.tz = map_info->points[y][x] * Z_SCALE;
			three_d(&scale.tx, &scale.ty, scale.tz);
			transformed_points[y][x].x = scale.tx + scale.center_x;
			transformed_points[y][x].y = scale.ty + scale.center_y;
			x++;
		}
		y++;
	}
}

t_point_args	init_args(int x, int y, int x1, int y1)
{
	t_point_args	args;

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
	t_point_args	args;

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
