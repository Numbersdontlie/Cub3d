/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:47:58 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/26 12:39:35 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	error_message(char *str, char **arr)
{
	if (arr)
		free_memory(arr);
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
}

void	error_exit(char *str, t_data *data, t_textinfo *text)
{
	if (text)
		free_text(text);
	if (data)
		ft_clean_exit(data);
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
}
