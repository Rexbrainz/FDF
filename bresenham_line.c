/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:00:57 by sudaniel          #+#    #+#             */
/*   Updated: 2024/11/26 17:00:07 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_scale_value(int f_height)
{
	if (f_height > 300)
		return (2);
	else if (f_height > 100)
		return (5);
	else if (f_height > 50)
		return (10);
	else
		return (30);
}

static int	my_abs(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

static int	check_pos(int x, int x1)
{
	if (x < x1)
		return (1);
	else
		return (-1);
}

void	bresenham_line(t_bline *l_p, t_map *map_info)
{
	while (l_p->x != l_p->x1 || l_p->y != l_p->y1)
	{
		if (l_p->y >= HEIGHT || l_p->y1 >= HEIGHT
			|| l_p->x >= WIDTH || l_p->x1 >= WIDTH
			|| l_p->y < 0 || l_p->y1 < 0
			|| l_p->x < 0 || l_p->x1 < 0)
			break ;
		if (l_p->z > 0 || l_p->z1 > 0)
			mlx_put_pixel(map_info->mlx_img, l_p->x, l_p->y, 0x00FF00FF);
		else
			mlx_put_pixel(map_info->mlx_img, l_p->x, l_p->y, 0xFFFFFFFF);
		l_p->scale_err = (2 * l_p->err);
		if (l_p->scale_err >= l_p->dy)
		{
			l_p->err += l_p->dy;
			l_p->x += l_p->sx;
		}
		if (l_p->scale_err <= l_p->dx)
		{
			l_p->err += l_p->dx;
			l_p->y += l_p->sy;
		}
	}
}

void	initialize_bline(t_point_args args,
	t_map *map_info, t_point **transformed_points)
{
	t_bline	l_p;

	l_p.x = transformed_points[args.y][args.x].x;
	l_p.y = transformed_points[args.y][args.x].y;
	l_p.z = map_info->points[args.y][args.x];
	l_p.x1 = transformed_points[args.y1][args.x1].x;
	l_p.y1 = transformed_points[args.y1][args.x1].y;
	l_p.z1 = map_info->points[args.y1][args.x1];
	l_p.dx = my_abs(l_p.x1 - l_p.x);
	l_p.dy = -my_abs(l_p.y1 - l_p.y);
	l_p.sx = check_pos(l_p.x, l_p.x1);
	l_p.sy = check_pos(l_p.y, l_p.y1);
	l_p.err = l_p.dx + l_p.dy;
	bresenham_line(&l_p, map_info);
}
