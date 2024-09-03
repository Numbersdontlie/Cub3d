/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:34:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/03 19:29:36 by kbolon           ###   ########.fr       */
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
	text = populate_floor_and_ceiling_values(text, grid);
	text->size = PIXELS;
	text = find_grid(text, grid);
	text->grid = remove_empty_lines(text->grid);
	if (!text->grid)
		error_message_text("ERROR: problems copying grid in init\n", text);
	return (text);
}

/*this function splits the rgb values for the floor and ceiling*/
t_textinfo	*populate_floor_and_ceiling_values(t_textinfo *text, char **grid)
{
	char		*temp;

	temp = find_floor_ceiling(grid, 'F');
	if (!temp)
		error_message_text("ERROR: floor values not found\n", text);
	text->floor_rgb = ft_split(temp, ',');
	free(temp);
	if (!text->floor_rgb)
		error_message_text("problem with splitting floor rgb", text);
	temp = find_floor_ceiling(grid, 'C');
	if (!temp)
		error_message_text("ERROR: ceiling values not found\n", text);
	text->ceiling_rgb = ft_split(temp, ',');
	free(temp);
	if (!text->ceiling_rgb)
		error_message_text("ERROR: problem with splitting floor rgb", text);
	return (text);
}

void	check_rgb_for_illegal_chars(t_textinfo *text, char **arr)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = row_count(arr);
	if (count < 3)
		error_message_text("ERROR: RGB not valid\n", text);
	while (i < count)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (ft_isdigit(arr[i][j]))
				j++;
			else
				error_message_text("ERROR: RGB not valid\n", text);
		}
		i++;
	}
}
