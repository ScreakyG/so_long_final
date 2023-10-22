/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 22:35:27 by fgonzale          #+#    #+#             */
/*   Updated: 2023/10/22 18:29:01 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_map_char(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'C')
				data->textures.collectibles_nb++;
			else if (data->map[i][j] == 'E')
				data->textures.exit_nb++;
			else if (data->map[i][j] == 'P')
				data->textures.player_nb++;
			else if (data->map[i][j] != '0' && data->map[i][j] != '1')
				exit_error(msg("Wrong map values", 1), data);
			j++;
		}
		i++;
	}
	if (data->textures.collectibles_nb == 0 || data->textures.exit_nb != 1
		|| data->textures.player_nb != 1)
		exit_error(msg("Error with map items", 1), data);
}

void	check_map(t_data *data, int height)
{
	int	i;
	int	j;

	i = -1;
	if (!data->map[0] || data->map[0][0] == '\0')
		exit_error(msg("File empty", 1), data);
	data->map_width = ft_strlen(data->map[0]);
	while (data->map[++i])
	{
		if ((int)ft_strlen(data->map[i]) != data->map_width)
			exit_error(msg("Map not rectangle", 1), data);
		j = -1;
		while (data->map[i][++j])
		{
			if (i == 0 && data->map[i][j] != '1')
				exit_error(msg("Map not closed", 1), data);
			if (j == 0 && data->map[i][j] != '1')
				exit_error(msg("Map not closed", 1), data);
			if (j == (data->map_width - 1) && data->map[i][j] != '1')
				exit_error(msg("Map not closed", 1), data);
			if (i == ((height - 1)) && data->map[i][j] != '1')
				exit_error(msg("Map not closed", 1), data);
		}
	}
}

static int	number_lines(char *map_arg, t_data *data)
{
	int		fd_map;
	int		count;
	char	*line;

	fd_map = open(map_arg, O_RDONLY);
	if (fd_map == -1)
		exit_error(msg(strerror(errno), 1), data);
	count = 0;
	line = get_next_line(fd_map);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd_map);
	}
	close(fd_map);
	return (count);
}

void	check_map_is_valid(t_data *data, char *map_arg)
{
	int		fd_map;
	char	*line;
	int		i;

	i = 0;
	fd_map = open(map_arg, O_RDONLY);
	if (fd_map == -1)
		exit_error(msg(strerror(errno), 1), data);
	data->map = malloc((number_lines(map_arg, data) + 1) * sizeof(char *));
	if (!data->map)
	{
		close(fd_map);
		exit_error(msg("Malloc map error", 1), data);
	}
	line = get_next_line(fd_map);
	while (line)
	{
		data->map[i] = ft_strtrim(line, "\n");
		free(line);
		i++;
		line = get_next_line(fd_map);
	}
	data->map[i] = NULL;
	data->map_height = i;
	close(fd_map);
}

void	check_map_format(char **argv, t_data *data)
{
	int	i;

	i = 0;
	if (ft_strlen(argv[1]) < 4)
		exit_error(msg("Map format is not correct", 1), data);
	while (argv[1][i])
		i++;
	i -= 4;
	if (!ft_strncmp(".ber", &argv[1][i], 4))
		return ;
	else
		exit_error(msg("Map format must be .ber", 1), data);
}
