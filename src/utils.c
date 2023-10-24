/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:33:34 by fgonzale          #+#    #+#             */
/*   Updated: 2023/10/24 04:31:40 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	**strs_strdup(char **strs, t_data *data)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc((data->map_height + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	while (i < data->map_height)
	{
		copy[i] = ft_strdup2(strs[i]);
		if (copy[i] == NULL)
			return (free_strs(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	destroy_all_xpm_images(t_data *data)
{
	if (data->textures.collectibles)
		mlx_destroy_image(data->mlx_ptr, data->textures.collectibles);
	if (data->textures.floor)
		mlx_destroy_image(data->mlx_ptr, data->textures.floor);
	if (data->textures.player)
		mlx_destroy_image(data->mlx_ptr, data->textures.player);
	if (data->textures.exit)
		mlx_destroy_image(data->mlx_ptr, data->textures.exit);
	if (data->textures.wall)
		mlx_destroy_image(data->mlx_ptr, data->textures.wall);
}

void	check_map_dimensions(t_data *data)
{
	if ((data->map_width * SPRITE_SIZE) > 1600
		|| (data->map_height * SPRITE_SIZE) > 900)
	{
		data->screen_width = 1600;
		data->screen_height = 900;
		data->scrolling_display = true;
	}
	else
	{
		data->screen_width = data->map_width * SPRITE_SIZE;
		data->screen_height = data->map_height * SPRITE_SIZE;
	}
	return ;
}

void	update_camera(int *camera_x, int *camera_y, t_data *data)
{
	t_pos	player;

	player = get_player_pos(data);
	*camera_x = (player.x * SPRITE_SIZE) - (1600 / 2);
	*camera_y = (player.y * SPRITE_SIZE) - (900 / 2);
	if (*camera_x < 0)
		*camera_x = 0;
	if (*camera_x > (data->map_width * SPRITE_SIZE) - 1600)
		*camera_x = (data->map_width * SPRITE_SIZE) - 1600;
	if (*camera_y < 0)
		*camera_y = 0;
	if (*camera_y > (data->map_height * SPRITE_SIZE) - 900)
	{
		*camera_y = (data->map_height * SPRITE_SIZE) - 900;
	}
}
