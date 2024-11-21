/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:00:57 by sudaniel          #+#    #+#             */
/*   Updated: 2024/11/21 17:16:10 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_bline	initialize_bline(int x, int y, int x1, int y1)
{
	t_bline	l_p;

	l_p.x = x;
	l_p.y = y;
	l_p.x1 = x1;
	l_p.y1 = y1;
	l_p.x *= 20;
	l_p.x1 *= 20;
	l_p.y *= 20;
	l_p.y1 *= 20;
	l_p.dx = my_abs(l_p.x1 - l_p.x);
	l_p.dy = my_abs(l_p.y1 - l_p.y);
	l_p.sx = check_pos(l_p.x, l_p.x1);
	l_p.sy = check_pos(l_p.y, l_p.y1);
	l_p.err = l_p.dx - l_p.dy;
	if (l_p.y >= HEIGHT || l_p.y1 >= HEIGHT
		|| l_p.x >= WIDTH || l_p.x1 >= WIDTH)
	{
		error("Error: Dimension over monitor's dimension.\n");
		exit(EXIT_FAILURE);
	}
	return (l_p);
}
