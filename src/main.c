/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 21:08:17 by fgonzale          #+#    #+#             */
/*   Updated: 2023/06/22 19:01:33 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	render(t_data *data)
{
	if (data->mlx_window)
	{
		create_map(data);
	}
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		exit_error(0, data);
	else if (keysym == XK_w || keysym == XK_W)
		move_player(0, -1, data);
	else if (keysym == XK_a || keysym == XK_A)
		move_player(-1, 0, data);
	else if (keysym == XK_s || keysym == XK_S)
		move_player(0, 1, data);
	else if (keysym == XK_d || keysym == XK_D)
		move_player(1, 0, data);
	return (0);
}

static void	init_data(t_data *data)
{
	data->map = NULL;
	data->mlx_ptr = NULL;
	data->mlx_window = NULL;
	data->textures.collectibles = NULL;
	data->textures.exit = NULL;
	data->textures.floor = NULL;
	data->textures.player = NULL;
	data->textures.wall = NULL;
	data->move_count = 0;
	data->textures.player_nb = 0;
	data->textures.collectibles_nb = 0;
	data->textures.exit_nb = 0;
}

static int	cross_close(t_data *data)
{
	exit_error(0, data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (msg("Need a '.ber' map as arg", 1));
	init_data(&data);
	check_map_format(argv, &data);
	check_map_is_valid(&data, argv[1]); // VOIR FEUILLE

	if (!(data.mlx_ptr = mlx_init()))
		exit_error(MLX_ERR, &data);
	if (!(data.mlx_window = mlx_new_window(data.mlx_ptr, SPRITE_SIZE * data.map_width, SPRITE_SIZE * data.map_height, "so_long")))
	{
		free(data.mlx_window); // PEUT ETRE ENLEVER ?
		exit_error(MLX_ERR, &data);
	}
	load_xpm_files(&data);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.mlx_window, KeyPress, KeyPressMask, &handle_keypress, &data); // FONCTION EXIT ESCAPE REFACTOR
	mlx_hook(data.mlx_window, DestroyNotify, 0, &cross_close, &data); // FONCTION EXIT ESCAPE REFACTOR
	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	free_strs(data.map);
	return (0);
}
