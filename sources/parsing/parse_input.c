/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:51:39 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/28 11:07:48 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*this fcn takes what is read by get_next_line & looks for
specific items and paths such as NO, SO, WE, EA & returns
an array with only*/
char	*find_cardinal_paths(char **arr, char *s)
{
	int		i;
	int		count;
	char	*path_found;
	char	*path_extension;

	i = -1;
	count = row_count(arr);
	while (++i < count)
	{
		if (!ft_strncmp(arr[i], s, 2))
		{
			path_found = ft_strdup(arr[i]);
			if (!path_found)
				error_message_simple("Memory Alloc failed", arr);
			path_extension = ft_strrchr(path_found, '.');
			if (path_extension)
			{
				path_extension = ft_strdup(path_extension);
				free (path_found);
				return (path_extension);
			}
		}
	}
	error_message_simple("ERROR: path not found", arr);
	return (NULL);
}

char*find_floor_ceiling(char **arr, int c)
{
	int		i;
	int		count;
	char	*path;

	i = -1;
	count = row_count(arr);
	while (++i < count)
	{
		if (arr[i][0] == c && arr[i][1] == ' ')
		{
			path = arr[i] + 2;
			while (*path && !ft_isdigit(*path))
				path++;
			if (*path)
			{
				path = ft_strdup(path);
				if (!path)
					error_message_simple("Error: mem alloc failed", arr);
				return (path);
			}
		}
	}
	perror("ERROR: RGB path not found\n");
	return (NULL);
}

char	**update_grid(char **arr, char *path)
{
	int		i;
	int		j;
	int		count;
	char	**grid;

	i = 0;
	j = 0;
	count = row_count(arr);
	grid = (char **)ft_calloc(count, sizeof(char *));
	if (!grid)
		error_message_simple("calloc failed updating .cub\n", arr);
	while (i < count)
	{
		if (ft_strnstr(arr[i], path, ft_strlen(arr[i])))
		{
			i++;
			continue ;
		}
		grid[j] = ft_strdup(arr[i]);
		j++;
		i++;
	}
	grid[j] = NULL;
	free_memory(arr);
	return (grid);
}

char	**remove_empty_lines(char **arr)
{
	int		i;
	int		j;
	int		count;
	char	**updated_grid;

	i = 0;
	j = 0;
	count = row_count(arr);
	updated_grid = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!updated_grid)
		error_message_simple("Memory alloc failed with trimming", arr);
	while (i < count)
	{
		if (arr[i] && ft_strlen(arr[i]) > 0)
		{
			updated_grid[j] = ft_strdup(arr[i]);
			j++;
		}
		i++;
	}
	free_memory(arr);
	return (updated_grid);
}
