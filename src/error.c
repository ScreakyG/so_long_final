/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 22:12:19 by fgonzale          #+#    #+#             */
/*   Updated: 2023/06/22 16:49:07 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	msg(char *str1, int exit_code)
{
	ft_putstr_fd("Error\n", 1);
	ft_putendl_fd(str1, 1);
	return (exit_code);
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
