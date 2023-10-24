/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:53:49 by fgonzale          #+#    #+#             */
/*   Updated: 2023/10/24 04:21:02 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define SPRITE_SIZE 32
# define MLX_ERR 1
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_RESET   "\x1b[0m"

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_pos
{
	int		x;
	int		y;
}	t_pos;

typedef struct s_text
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectibles;
	void	*exit;
	int		collectibles_nb;
	int		player_nb;
	int		exit_nb;
}	t_textures;

typedef struct s_struct
{
	char		**map;
	int			map_width;
	int			map_height;
	int			screen_width;
	int			screen_height;
	bool		scrolling_display;
	void		*mlx_ptr;
	void		*mlx_window;
	int			move_count;
	t_textures	textures;
}	t_data;

/* Map Check*/

void	check_map_format(char **argv, t_data *data);
void	check_map_is_valid(t_data *data, char *map_arg);
void	check_map(t_data *data, int height);
void	check_map_char(t_data *data);
int		path_valid(char **map, t_pos obj, t_pos player);
void	map_paths_valid(t_data *data);

/* Map Creation */

void	create_map(t_data *data);
void	load_xpm_files(t_data *data);
void	check_map_dimensions(t_data *data);
void	update_camera(int *camera_x, int *camera_y, t_data *data);

/* Player Movement */

t_pos	get_player_pos(t_data *data);
void	move_player(int x, int y, t_data *data, t_pos player_pos);

/* Exit */

int		msg(char *str1, int exit_code);
void	exit_error(int exit_code, t_data *data);
int		cross_close(t_data *data);
void	exit_win(t_data *data);

/* UTILS */

char	**strs_strdup(char **strs, t_data *data);
void	free_strs(char **strs);
void	destroy_all_xpm_images(t_data *data);

/* Input Handling */

int		render(t_data *data);
int		handle_keypress(int keysym, t_data *data);

#endif
