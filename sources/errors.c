/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:47:58 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/23 12:03:49 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	error_message(char *str)
{
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
}

void	error_message_simple(char *str, char **arr)
{
	if (arr)
		free_memory(arr);
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
}

void	error_message_text(char *str, t_textinfo *text)
{
	free_text(text);
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
}

void	error_message_data(char *str, t_data *data, t_textinfo *text)
{
	if (text)
		free_text(text);
	ft_putstr_fd(str, 2);
	ft_clean_exit(data);
/*	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
	free (data);*/
	exit (EXIT_FAILURE);
}

int	ft_wrapper_exit(t_data *data)
{
	ft_clean_exit(data);
	return (0);
}