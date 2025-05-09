/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 06:57:02 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/11 17:23:16 by sudaniel         ###   ########.fr       */
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
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# define WIDTH 1920
# define HEIGHT 1080
# define Z_SCALE 10

typedef struct s_map
{
	int			height;
	int			width;
	int			**points;
	mlx_image_t	*mlx_img;	
}		t_map;

typedef struct s_bline
{
	int		x;
	int		x1;
	int		y;
	int		y1;
	int		z;
	int		z1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		scale_err;
}		t_bline;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_point_args
{
	int	x;
	int	y;
	int	x1;
	int	y1;
}	t_point_args;

typedef struct scale
{
	int	tx;
	int	ty;
	int	tz;
	int	scale_f;
	int	center_x;
	int	center_y;
}		t_scale;

// error: Takes an error message, displays it and exits the program.
void	error(const char *error_message);

//	dealloc_and_error:	Another variant of error, this time it takes
//						the error message and a pointer to the 
//						allocated memory which it frees.
void	dealloc_and_error(const char *error_message, t_map *map_info);

// get_map_details:	Takes a valid map, and the t_map struct. it uses the map
// 					to initialize the t_map struct.
void	get_map_details(char *map, t_map *map_info);

//	connect_coordinates: Takes the map info, applies isometric view to them
//						 and draw lines between points.
void	connect_coordinates(t_map *map_info);

//	initialize_bline:	Takes the points, initialized in args, the map_info and
//						the transformed points, to initialze the necessary
//						variables for the bresenham line algorithm.
void	initialize_bline(t_point_args args,
			t_map *map_info, t_point **transformed_points);

//	get_scale_value: Takes the map_height, and returns a scaling value based on
//					 the range the map_height falls in.
int		get_scale_value(int f_height);

//	free_memory:	Takes the map_info and frees the memory space allocated.
void	free_memory(t_map *map_info);

#endif
