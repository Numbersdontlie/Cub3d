/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:27:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/03 19:32:34 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	copy_valid_lines(char *grid, char *trimmed, char **arr)
{
	grid = ft_strdup(trimmed);
	if (!grid)
		error_message_simple("ERROR: mem alloc failed\n", arr);
}

void	check_empty_lines(char **grid, int i)
{
	if (i == 0)
		error_message_simple("ERROR: Grid is empty after removing empty lines\n", grid);
}
