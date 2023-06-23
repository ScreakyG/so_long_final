/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_paths_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:08:53 by fgonzale          #+#    #+#             */
/*   Updated: 2023/06/23 16:15:30 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	path_valid(char **map, t_pos player, t_pos obj)
{
	if (obj.y == player.y && obj.x == player.x)
		return (1);
	if (map[player.y][player.x] == 'C' || map[player.y][player.x] == '0'
		|| map[player.y][player.x] == 'P')
	{
		map[player.y][player.x] = 'V';
		if (path_valid(map, (t_pos){player.x, player.y - 1}, obj))
			return (1);
		if (path_valid(map, (t_pos){player.x - 1, player.y}, obj))
			return (1);
		if (path_valid(map, (t_pos){player.x, player.y + 1}, obj))
			return (1);
		if (path_valid(map, (t_pos){player.x + 1, player.y}, obj))
			return (1);
	}
	return (0);
}

void	map_paths_valid(t_data *data)
{
	int		i;
	int		j;
	char	**map_copy;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'C' || data->map[i][j] == 'E')
			{
				map_copy = strs_strdup(data->map, data);
				if (!map_copy)
					exit_error(msg("Copy map malloc error", 1), data);
				if (!path_valid(map_copy, get_player_pos(data), (t_pos){j, i}))
				{
					free_strs(map_copy);
					exit_error(msg("No valid paths for collectible", 1), data);
				}
				free_strs(map_copy);
			}
		}
	}
}
