/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:02:59 by sudaniel          #+#    #+#             */
/*   Updated: 2024/11/26 12:50:32 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(char *error_message)
{
	ft_printf(error_message);
	exit(EXIT_FAILURE);
}

static void	escape(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(param);
}

static void	free_memory(t_map *map_info)
{
	int	i;

	i = 0;
	while (i < map_info->height)
	{
		free(map_info->points[i]);
		i++;
	}
	free(map_info->points);
}

int	main(int argc, char **argv)
{
	char		*map;
	t_map		map_info;
	mlx_t		*mlx;

	if (argc != 2)
		error("Error\nUsage: Program-name map\n");
	map = ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1]));
	if (map == NULL || map[4])
		error("Error\nInvalid file!: File must end with .fdf\n");
	get_map_details(argv[1], &map_info);
	mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!mlx)
		error("Error: Mlx could not be initialized\n");
	map_info.mlx_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!map_info.mlx_img)
		error("Error: Image could not be created\n");
	mlx_image_to_window(mlx, map_info.mlx_img, 0, 0);
	connect_coordinates(&map_info);
	mlx_key_hook(mlx, escape, mlx);
	mlx_loop(mlx);
	free_memory(&map_info);
	mlx_terminate(mlx);
	return (0);
}
