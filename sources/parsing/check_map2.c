/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:27:01 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/14 17:04:04 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	filter_grid_lines(t_textinfo *text, char **grid)
{
	int	start;

	start = find_grid_start(grid);
	text->grid = copy_grid(text, grid, start);
}

char	**copy_grid(t_textinfo *text, char **grid, int start)
{
	int		j;
	int		count;
	char	**temp;

	j = 0;
	count = row_count(grid);
	temp = (char **)malloc((count + 1) * sizeof(char *));
	if (!temp)
		return (NULL);
	while (grid[start] != NULL && (ft_strchr(grid[start], '1') || \
		ft_strchr(grid[start], '0')))
	{
		temp[j] = ft_strdup(grid[start]);
		if (!temp[j])
		{
//			free_partials((void **)temp);
			while (j > 0)
				free(temp[--j]);
			free(temp);
			free_memory(grid);
			error_exit("ERROR: problems copying grid\n", NULL, text);
			return (NULL);
		}
		j++;
		start++;
	}
	temp[j] = NULL;
	return (temp);
}

/*function looks for paths to textures or if the grid is empty*/
int	find_grid_start(char **grid)
{
	int		i;

	i = 0;
	while (ft_strstr(grid[i], "NO") || ft_strstr(grid[i], "SO") || \
		ft_strstr(grid[i], "WE") || ft_strstr(grid[i], "EA") || \
		ft_strstr(grid[i], "F") || ft_strstr(grid[i], "C") || \
		ft_strlen(grid[i]) == 0)
	{
		i++;
	}
	return (i);
}
