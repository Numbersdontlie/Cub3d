/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:47:17 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/14 17:12:19 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	error_malloc(char *s)
{
	ft_putstr_fd(s, 2);
	exit (EXIT_FAILURE);
	return (0);
}

void free_paths(char *str, char **paths, int count)
{
	int i;

	i = 0;
	while ( i < count)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	error_message_simple(str, NULL);
}
