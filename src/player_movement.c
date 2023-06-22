/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:23:22 by fgonzale          #+#    #+#             */
/*   Updated: 2023/06/22 17:46:25 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_pos	get_player_pos(t_data *data)
{
	t_pos	player_pos;

	player_pos.y = 0;
	while (data->map[player_pos.y])
	{
		player_pos.x = 0;
		while (data->map[player_pos.y][player_pos.x])
		{
			if (data->map[player_pos.y][player_pos.x] == 'P')
				return (player_pos);
			player_pos.x++;
		}
		player_pos.y++;
	}
	return ((t_pos){0, 0});
}

void	move_player(int x, int y, t_data *data)
{
	t_pos	player_pos;

	player_pos = get_player_pos(data);
	if (data->map[player_pos.y + y][player_pos.x + x] != '1')
	{
		if (data->map[player_pos.y + y][player_pos.x + x] == '0')
		{
			data->map[player_pos.y + y][player_pos.x + x] = 'P';
			data->map[player_pos.y][player_pos.x] = '0';
		}
		else if (data->map[player_pos.y + y][player_pos.x + x] == 'C')
		{
			data->map[player_pos.y + y][player_pos.x + x] = 'P';
			data->map[player_pos.y][player_pos.x] = '0';
			data->textures.collectibles_nb--;
		}
		else if (data->map[player_pos.y + y][player_pos.x + x] == 'E')
		{
			if (data->textures.collectibles_nb == 0)
			{
				data->map[player_pos.y + y][player_pos.x + x] = 'P';
				data->map[player_pos.y][player_pos.x] = '0';
				mlx_destroy_window(data->mlx_ptr, data->mlx_window);
				destroy_all_xpm_images(data);
				data->mlx_window = NULL;
			}
			else
				return ;
		}
		printf("Player movements count = %d\n", ++data->move_count);
	}
}
