/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:52:13 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/12 17:05:45 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_mapstruct(t_data *data)
{
	if (data->mapinfo)
	{
		free(data->mapinfo);
		data->mapinfo = NULL;
	}
}

void free_partial(void **array, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}