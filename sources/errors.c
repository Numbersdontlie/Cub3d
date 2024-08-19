/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:47:58 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/19 21:53:13 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	error_message(char *str)
{
	ft_putendl_fd(str, 2);
	exit (1);
}

void	error_message_simple(char *str, char **arr)
{
	if (arr)
		free_memory(arr);
	ft_putendl_fd(str, 2);
	exit (1);
}

void	ft_malloc_error(void)
{
	perror("Problem with memory allocation");
	exit(EXIT_FAILURE);
}
