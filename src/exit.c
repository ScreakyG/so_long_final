/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 22:12:19 by fgonzale          #+#    #+#             */
/*   Updated: 2023/06/23 17:16:56 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	msg(char *str1, int exit_code)
{
	ft_putstr_fd("Error\n", 1);
	ft_putendl_fd(str1, 1);
	return (exit_code);
}

void	exit_win(t_data *data)
{
	ft_printf("Player movements count = %d\n", ++data->move_count);
	ft_printf(ANSI_COLOR_GREEN "YOU WON !\n" ANSI_COLOR_RESET);
	exit_error(0, data);
}

void	exit_error(int exit_code, t_data *data)
{
	if (data->mlx_window)
		mlx_destroy_window(data->mlx_ptr, data->mlx_window);
	destroy_all_xpm_images(data);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (data->map)
		free_strs(data->map);
	exit(exit_code);
}

int	cross_close(t_data *data)
{
	exit_error(0, data);
	return (0);
}
