/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 06:57:02 by sudaniel          #+#    #+#             */
/*   Updated: 2024/11/21 11:55:28 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include "new_libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_map
{
	int			height;
	int			width;
	int			**points;
	mlx_image_t	*mlx_img;	
}		t_map;

typedef struct s_bline
{
	int	x;
	int	x1;
	int	y;
	int	y1;
	int	z;
	int z1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	scale_err;
}		t_bline;

// error: Takes an error message, displays it and exits the program.
void	error(char *error_message);

// get_map_details:	Takes a valid map, and the t_map struct. it uses the map
// 					to initialize the t_map struct.
void	get_map_details(char *map, t_map *map_info);
void	connect_coordinates(t_map *map_info);
t_bline	initialize_bline(int x, int y, int x1, int y1);
#endif
