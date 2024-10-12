/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:34:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/10/12 10:16:51 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//function initializes the text struct and saves it in our data struct
t_textinfo	*ft_initialize_info(char **arr)
{
	char		**grid;
	t_textinfo	*text;

	grid = read_map(*arr);
	if (!grid)
		error_message("ERROR: problem reading map");
	text = (t_textinfo *) ft_calloc (1, sizeof(t_textinfo));
	if (!text)
		error_message_simple("ERROR: calloc fail in text_init", grid);
	if (fill_paths(text, grid) == EXIT_FAILURE)
		error_exit("ERROR: calloc fail in text_init", NULL, text);
	text->ceiling_rgb = populate_rgb_values(text, grid, 'C', \
		&text->hex_ceiling);
	text->floor_rgb = populate_rgb_values(text, grid, 'F', &text->hex_floor);
//	text->size = PIXELS;
	text = find_grid(text, grid);
	if (!text->grid)
		error_message_text("ERROR: problems copying grid in init\n", text);
	free_memory(grid);
	return (text);
}

//function creates the path array needed to store our wall paths.  We need it
//in an char array to help load the textures in a while loop later
int	fill_paths(t_textinfo *text, char **grid)
{
	text->paths = (char **) ft_calloc(5, sizeof(char *));
	if (!text->paths)
		return (error_message_simple("ERROR: problems callocing paths\n", NULL));
	text->paths[0] = find_cardinal_paths(grid, "NO");
	if (!text->paths[0])
		return (error_message_simple("ERROR: north path not found\n", NULL));
	text->paths[1] = find_cardinal_paths(grid, "EA");
	if (!text->paths[1])
		return (error_message_simple("ERROR: east path not found\n", NULL));
	text->paths[2] = find_cardinal_paths(grid, "SO");
	if (!text->paths[2])
		return (error_message_simple("ERROR: south path not found\n", NULL));
	text->paths[3] = find_cardinal_paths(grid, "WE");
	if (!text->paths[3])
		return (error_message_simple("ERROR: west path not found\n", NULL));
	text->paths[4] = NULL;
	return (EXIT_SUCCESS);
}

/*this function splits the rgb values for the floor and ceiling
checks the rgb value is within expectations, converts it to an int and
saves as an int array and converts it to a hex value*/
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
		error_exit("ERROR: problem with allocating rgb", NULL, text);
	}
	while (++i < 3)
	{
		rgb[i] = ft_atoi(arr[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free(rgb);
			free_memory(arr);
			error_exit("ERROR: rgb is not valid", NULL, text);
		}
	}
	*hex_value = ((rgb[0] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + \
		(rgb[2] & 0xff);
	return (rgb);
}

/*funcion finds the rgb values in the .cub file, makes a char array and check for
illegal characters too (empty or letters etc) and converts rgb values to hex.*/
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
		error_exit("ERROR: floor/ceiling values not found\n", NULL, text);
	}
	arr = ft_split(temp, ',');
	free(temp);
	if (!arr)
	{
		free_memory(grid);
		error_exit("problem with splitting rgb", NULL, text);
	}
	if (check_rgb_for_illegal_chars(arr) == EXIT_FAILURE)
	{
		free_memory(grid);
		error_exit("problem with splitting rgb", NULL, text);
	}
	rgb = validate_and_convert(text, arr, hex_value);
	free_memory(arr);
	return (rgb);
}

/*function checks if less than 3 values are provided, if
a character is not a digit etc*/
int	check_rgb_for_illegal_chars(char **arr)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	count = row_count(arr);
	if (count < 3)
		error_exit("ERROR: RGB not valid\n", NULL, NULL);
	while (++i < count)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (ft_isdigit(arr[i][j]))
				j++;
			else
				error_exit("ERROR: RGB not valid\n", NULL, NULL);
		}
	}
	return (EXIT_SUCCESS);
}
