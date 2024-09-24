/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:34:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/24 10:14:35 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Function to initialize the textures information
//structure, it initialize all to NULL and 0
//except for the size, which is initialized to PIXELS (64)
t_textinfo	*ft_initialize_textinfo(char **arr)
{
	char		**grid;
	t_textinfo	*text;

	grid = read_map(*arr);
	if (!grid)
		error_message("ERROR: problem reading map");
	text = (t_textinfo *) ft_calloc (1, sizeof(t_textinfo));
	if (!text)
		error_message_simple("ERROR: calloc fail in text_init", grid);
	text->north = find_cardinal_paths(grid, "NO");
	text->south = find_cardinal_paths(grid, "SO");
	text->west = find_cardinal_paths(grid, "WE");
	text->east = find_cardinal_paths(grid, "EA");
	text->ceiling_rgb = populate_rgb_values(text, grid, 'C', \
		&text->hex_ceiling);
	text->floor_rgb = populate_rgb_values(text, grid, 'F', &text->hex_floor);
	text->size = PIXELS;
	text = find_grid(text, grid);
	if (!text->grid)
		error_message_text("ERROR: problems copying grid in init\n", text);
	free_memory(grid);
	return (text);
}

/*this function splits the rgb values for the floor and ceiling*/
int	*validate_and_convert(t_textinfo *text, char **arr, \
	unsigned long *hex_value)
{
	int		*rgb;
	int		i;

	i = -1;
	rgb = ft_calloc(3, sizeof(int));
	if (!rgb)
	{
		free_memory(arr);
		error_message_text("ERROR: problem with allocating rgb", text);
	}
	while (++i < 3)
	{
		rgb[i] = ft_atoi(arr[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free(rgb);
			free_memory(arr);
			error_message_text("ERROR: rgb is not valid", text);
		}
	}
	*hex_value = ((rgb[0] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + \
		(rgb[2] & 0xff);
	return (rgb);
}

int	*populate_rgb_values(t_textinfo *text, char **grid, int c, 
	unsigned long *hex_value)
{
	char	*temp;
	char	**arr;
	int		*rgb;

	temp = find_floor_ceiling(text, grid, c);
	if (!temp)
	{
		free_memory(grid);
		error_message_text("ERROR: floor/ceiling values not found\n", text);
	}
	arr = ft_split(temp, ',');
	free(temp);
	if (!arr)
	{
		free_memory(grid);
		error_message_text("problem with splitting rgb", text);
	}
	if (check_rgb_for_illegal_chars(arr) == EXIT_FAILURE)
	{
		free_memory(grid);
		error_message_text("problem with splitting rgb", text);
	}
	rgb = validate_and_convert(text, arr, hex_value);
	free_memory(arr);
	return (rgb);
}


int	check_rgb_for_illegal_chars(char **arr)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	count = row_count(arr);
	if (count < 3)
		error_message("ERROR: RGB not valid\n");
	while (++i < count)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (ft_isdigit(arr[i][j]))
				j++;
			else
				error_message("ERROR: RGB not valid\n");
		}
	}
	return (EXIT_SUCCESS);
}

//Function to initialize the textures information
//structure, it initialize all to NULL and 0
//except for the size, which is initialized to PIXELS (64)
void	ft_init_textinfo(t_textinfo *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = 0;
	textures->ceiling = 0;
	textures->hex_ceiling = 0x0;
	textures->hex_floor = 0x0;
	textures->size = PIXELS;
	textures->step = 0.0;
	textures->position = 0.0;
	textures->x = 0;
	textures->y = 0;
	textures->floor_rgb = 0;
	textures->ceiling_rgb = 0;
}

//Function to initialize a 2D array of pixel values
//it checks if the texture is already allocated and free it if neccesary
//it allocate memory for each row of of texture pixel
void	ft_initialize_texture_pixels(t_data *data)
{
	int	i;

	if (data->texture_pixels)
		free(data->texture_pixels);
	data->texture_pixels = ft_calloc(HEIGHT + 1, sizeof * data->texture_pixels);
	if (!data->texture_pixels)
		ft_clean_exit(data);
	i = 0;
	while (i < HEIGHT)
	{
		data->texture_pixels[i] = ft_calloc(WIDTH + 1, sizeof * data->texture_pixels);
		if (!data->texture_pixels[i])
			ft_clean_exit(data);
		i++;
	}
}
