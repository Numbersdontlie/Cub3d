/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:52:13 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/30 10:52:26 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_mapstruct(t_data *data)
{
	if (data->mapinfo->grid)
	{
		free_memory(data->mapinfo->grid);
		data->mapinfo->grid = NULL;
	}
	if (data->mapinfo)
	{
		free(data->mapinfo);
		data->mapinfo = NULL;
	}
}
