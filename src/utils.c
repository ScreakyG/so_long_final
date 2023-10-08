/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:33:34 by fgonzale          #+#    #+#             */
/*   Updated: 2023/10/08 12:59:14 by fgonzale         ###   ########.fr       */
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
