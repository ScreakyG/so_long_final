/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:32:45 by fgonzale          #+#    #+#             */
/*   Updated: 2023/10/24 14:29:48 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_xpm_load(t_data *data)
{
	if (!data->textures.collectibles)
		exit_error(1, data);
	if (!data->textures.floor)
		exit_error(1, data);
	if (!data->textures.player)
		exit_error(1, data);
	if (!data->textures.exit)
		exit_error(1, data);
	if (!data->textures.wall)
		exit_error(1, data);
}

void	load_xpm_files(t_data *data)
{
	int	width;
	int	height;

	data->textures.wall = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/wall.xpm", &width, &height);
	data->textures.collectibles = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/collectibles.xpm", &width, &height);
	data->textures.exit = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/portal.xpm", &width, &height);
	data->textures.player = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/player.xpm", &width, &height);
	data->textures.floor = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/floor.xpm", &width, &height);
	check_xpm_load(data);
}

static void	put_images(t_data *data, char c, int i, int j)
{
	int	x;
	int	y;

	data->camera.x = 0;
	data->camera.y = 0;
	if (data->scrolling_display == true)
		update_camera(data);
	x = j * SPRITE_SIZE - data->camera.x;
	y = i * SPRITE_SIZE - data->camera.y;
	if (c == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_window,
			data->textures.wall, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_window,
			data->textures.collectibles, x, y);
	else if (c == '0')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_window,
			data->textures.floor, x, y);
	else if (c == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_window,
			data->textures.exit, x, y);
	else if (c == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_window,
			data->textures.player, x, y);
}

void	create_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
			put_images(data, data->map[i][j], i, j);
	}
}
