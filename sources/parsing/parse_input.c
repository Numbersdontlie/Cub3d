/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:51:39 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/29 08:49:49 by kbolon           ###   ########.fr       */
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
			path_found = ft_strdup(arr[i] + 2);
			if (!path_found)
			{
				error_no_exit("ERROR: Memory Alloc failed\n", arr);
				return (NULL);
			}
			path_extension = path_extractor(arr, path_found);
			return (path_extension);
		}
	}
	error_message("ERROR: path not found\n", arr);
	return (NULL);
}

char 	*path_extractor(char **arr, char *str)
{
	char	*path;
	int		i;

	i = 0;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
		i++;
	path = ft_strdup(&str[i]);
	if (!path)
	{
		free (str);
		error_message("ERROR: Memory Alloc failed\n", arr);
	}
	free (str);
	return (path);
}

char	*find_floor_ceiling(t_textinfo *text, char **arr, int c)
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
			if (*path && (path = ft_strdup(path)))
				return (path);
			free_memory(arr);
			error_exit("ERROR: mem alloc failed\n", NULL, text);
		}
	}
	return(error_message("ERROR: RGB path not found\n", arr), NULL);
}

char	**remove_empty_lines(char **arr)
{
	int		i;
	int		j;
	char	**updated_grid;
	char	*trimmed;

	j = 0;
	i = row_count(arr);
	updated_grid = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!updated_grid)
		error_message("ERROR: Memory alloc failed with trimming\n", arr);
	i = 0;
	while (arr[i] != NULL)
	{
		trimmed = ft_trim_line(arr[i]);
		if (*trimmed != '\0')
		{
			copy_valid_lines(updated_grid[j], trimmed, arr);
			j++;
		}
		i++;
	}
	check_empty_lines(updated_grid, j);
	free_memory(arr);
	return (updated_grid);
}

t_textinfo	*find_grid(t_textinfo *text, char **grid)
{
	char	**temp;
	int		i;
	int		j;

	j = 0;
	i = row_count(grid);
	temp = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!temp)
		error_message("ERROR: calloc fail in text_init", grid);
	i = 0;
	while (grid[i] != NULL)
	{
		if (filter_grid_lines(grid[i]) == 0)
		{
			temp[j] = ft_strdup(grid[i]);
			if (!temp[j])
				error_exit("ERROR: problems copying grid\n",  NULL, text);
			j++;
		}
		i++;
	}
	temp[j] = NULL;
	text->grid = temp;
	return (text);
}

int	filter_grid_lines(char *grid)
{
	if (ft_strstr(grid, "NO") || ft_strstr(grid, "SO") || ft_strstr(grid, "WE") \
	|| ft_strstr(grid, "EA") || ft_strstr(grid, "F") || ft_strstr(grid, "C") || \
	ft_strlen(grid) == 0)
		return (1);
	return (0);
}
