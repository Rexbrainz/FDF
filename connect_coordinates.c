/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_coordinates.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:40:08 by sudaniel          #+#    #+#             */
/*   Updated: 2024/11/21 18:00:55 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	three_d(int *x, int *y, int z)
{
	int	temp;

	temp = *x;
	*x = (temp - *y) * cos(0.523599) + WIDTH / 2;
	*y = (temp + *y) * sin(0.523599) - z + HEIGHT / 2;
}

static void	bresenham_line(t_bline *l_p, t_map *map_info)
{
	l_p->z = map_info->points[l_p->y / 20][l_p->x / 20];
	l_p->z1 = map_info->points[l_p->y1 / 20][l_p->x1 / 20];
	three_d(&l_p->x, &l_p->y, l_p->z);
	three_d(&l_p->x1, &l_p->y1, l_p->z1);
	if (l_p->y >= HEIGHT || l_p->y1 >= HEIGHT
		|| l_p->x >= WIDTH || l_p->x1 >= WIDTH)
	{
		error("Error: Dimension over monitor's dimension.\n");
		exit(EXIT_FAILURE);
	}
	while (l_p->x != l_p->x1 || l_p->y != l_p->y1)
	{
		if (l_p->z)
			mlx_put_pixel(map_info->mlx_img, l_p->x, l_p->y, 0x00FF00FF);
		else
			mlx_put_pixel(map_info->mlx_img, l_p->x, l_p->y, 0xFFFFFFFF);
		l_p->scale_err = 2 * l_p->err;
		if (l_p->scale_err > -l_p->dy)
		{
			l_p->err -= l_p->dy;
			l_p->x += l_p->sx;
		}
		if (l_p->scale_err < l_p->dx)
		{
			l_p->err += l_p->dx;
			l_p->y += l_p->sy;
		}
	}
}

void	connect_coordinates(t_map *map_info)
{
	int		x;
	int		y;
	t_bline	l_p;

	y = 0;
	while (y < map_info->height)
	{
		x = 0;
		while (x < map_info->width)
		{
			if (x < map_info->width - 1)
			{
				l_p = initialize_bline(x, y, x + 1, y);
				bresenham_line(&l_p, map_info);
			}
			if (y < map_info->height - 1)
			{
				l_p = initialize_bline(x, y, x, y + 1);
				bresenham_line(&l_p, map_info);
			}
			x++;
		}
		y++;
	}
}
