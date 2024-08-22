/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:51:39 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/22 13:15:46 by kbolon           ###   ########.fr       */
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
	char	*path;

	i = 0;
	count = row_count(arr);
	while (i < count)
	{
		if (!ft_strncmp(arr[i], s, 2))
		{
			path = ft_strdup(arr[i]);
			path = ft_strrchr(path, '.');
			if (path)
			{
//				free(arr[i]);//how to erase the line in arr??
//				arr[i] = NULL;
				return (path);
			}
		}
		i++;
	}
	perror("ERROR: path not found\n");
	return (NULL);
}

char	*find_floor_ceiling(char **arr, int c)
{
	int		i;
	int		count;
	char	*path;

	i = 0;
	count = row_count(arr);
	while (i < count)
	{
		path = ft_strchr(arr[i], c);
		if (path != NULL)
		{
			path++;
			while (*path && !ft_isdigit(*path))
				path++;
			if (*path)
			{
				path = ft_strdup(path);
				return (path);
			}
		}
		i++;
	}
	perror("ERROR: path not found\n");
	return (NULL);
}

/*int	check_access(char *path)
{
	if (access(cmd->file_name, F_OK | W_OK) == -1)
	{
		perror("ERROR: Path not found");
		return (1);
	}
	return (0);
}*/


/*	path->fd_in = open(node->file_name, O_RDONLY, 0);
		if (check_access_and_fd(node, node->fd_in, 0) == 0)
			node->fd_out = -1;
	}
	else if (fd_type == 1)
	{
		node->fd_out = open(node->file_name, instructions, 0777);
		if (check_access_and_fd(node, 0, node->fd_out) == 0)
			node->fd_in = -1;
	}
	else if (!fd_type)
	{
		node->fd_in = -1;
		node->fd_out = -1;
	}
	return (node);
}*/