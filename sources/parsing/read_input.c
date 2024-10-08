/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:14:37 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/08 12:56:00 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_extension(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 4 || ft_strncmp(&s[len - 4], ".cub", len - 4) != 0)
		return (EXIT_FAILURE);
		//error_exit("ERROR: please include a .cub file\n", NULL, NULL);
}

size_t	row_count(char **grid)
{
	size_t	i;

	i = 0;
	if (!grid)
		return (0);
	while (grid[i])
		i++;
	return (i);
}

/*This function reads the .cub file.
The number of characters read per line impacts the game's resolution.
Based on a 1920x1080 resolution with 64x64 pixel tiles, the game can display
30 tiles horizontally (1920/64) and 16 tiles vertically (1080/64).*/
char	**read_map(char *s)
{
	int		fd;
	char	**arr;
	int		i;
	int		size;

	i = 0;
	size = 100;
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("ERROR: unable to open file \n", 2);
		return (NULL);
	}
	arr = NULL;
	arr = (char **) malloc (sizeof(char *) * size); 
	if (!arr)
	{
		close (fd);
		return (NULL);
	}
	arr = graphic_gnl(size, fd, arr, i);
	close(fd);
	if (!arr)
		return (NULL);
	i = row_count(arr);
	if (i < 2)
	{
		free_memory(arr);
		ft_putstr_fd("ERROR: empty file\n", 2);
		return (NULL);
	}
	return (arr);
}

char	*ft_replace(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			s[i] = '\0';
		i++;
	}
	return (s);
}

char	**graphic_gnl(int size, int fd, char **arr, int i)
{
	char	*test;

	while (1)
	{
		if (i >= size - 1)
		{
			size *= 2;
			arr = (char **) malloc (sizeof(char *) * size);
			if (!arr)
				return (NULL);
		}
		test = get_next_line(fd);
		if (test == NULL)
			break ;
		arr[i] = ft_strdup(test);
		ft_replace(arr[i]);
		free(test);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

/*Function to get the number of lines inside the map.*/
int	ft_get_lines(char *s)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("ERROR: unable to open file \n", 2);
		return (NULL);
	}
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			count++;
			free (line);
			line = get_next_line(fd);
		}
		close (fd);
	}
	return (count);
}

//Function to parse the data
//Creating a new one since I don't want to break the work done so far
//just for testing
void	ft_parse_data(char *path_to_file, t_data *data)
{
	int	i;
	int	row;
	int	column;

	i = 0;
	row = 0;
	column = 0;
	data->mapinfo->num_of_lines = ft_get_lines(path_to_file);
	data->mapinfo->path = path_to_file;
	data->mapinfo->grid = ft_calloc(data->mapinfo->num_of_lines + 1, sizeof(char *));
	if (!data->mapinfo->grid)
	{
		error_message("problem with malloc\n");
		return ;
	}
	data->mapinfo->fd = open(path_to_file, O_RDONLY);
	if (data->mapinfo->fd < 0)
	{
		error_message("problem opening the file\n");
		return ;
	}
	else
	{
		
	}
}
