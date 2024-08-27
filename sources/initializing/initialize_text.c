/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:34:42 by kbolon            #+#    #+#             */
/*   Updated: 2024/08/27 18:31:09 by kbolon           ###   ########.fr       */
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
	{
		free_memory(grid);
		error_message_simple("ERROR: calloc fail in text_init", grid);
	}
	grid = update_text_info(&text->north, grid, "NO");
	grid = update_text_info(&text->south, grid, "SO");
	grid = update_text_info(&text->west, grid, "WE");
	grid = update_text_info(&text->east, grid, "EA");
	text = populate_floor_and_ceiling_values(text, grid);
	text->size = PIXELS;
	return (text);
}

/*this function splits the rgb values for the floor and ceiling*/
t_textinfo	*populate_floor_and_ceiling_values(t_textinfo *text, char **grid)
{
	char		*temp;

	temp = find_floor_ceiling(grid, 'F');
	grid = update_grid(grid, (char *)temp);
	text->floor_rgb = ft_split(temp, ',');
	if (!text->floor_rgb)
		error_message_text("problem with splitting floor rgb", text);
	temp = find_floor_ceiling(grid, 'C');
	grid = update_grid(grid, temp);
	text->ceiling_rgb = ft_split(temp, ',');
	if (!text->ceiling_rgb)
				error_message_text("problem with splitting floor rgb", text);
	text->grid = remove_empty_lines(grid);
	return (text);
}
/*this function updates the grid by removing the path from the .cub file*/
char	**update_text_info(char **path, char **grid, char *s)
{
	char		**temp_grid;

	*path = find_cardinal_paths(grid, s);
	temp_grid = update_grid(grid, *path);
	return (temp_grid);
}
