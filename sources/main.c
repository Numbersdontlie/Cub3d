/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:41:29 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/17 17:16:58 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void check_args(t_textinfo *text)
{
	valid_chars(text);
	check_map_items(text);
	flood_fill(text->grid);
}

int	main(int ac, char **av)
{
	t_textinfo	*text;
	t_data		*data;

	if (ac != 2)
		error_message("ERROR: include ./cub3D & .cub\n");
	check_extension(av[1]);
	text = ft_initialize_textinfo(&av[1]);
	if (!text)
		error_message("ERROR: problem loading text");
	check_args(text);
	data = ft_initialize_data(text);
	if (!data)
		error_message_text("ERROR: problem loading text", text);
	if (ft_initialize_connection(data) == EXIT_FAILURE)
		error_message_data("ERROR: problem initiating connection\n", data, text);
	if (ft_initialize_textures(data) == EXIT_FAILURE)
		error_message_data("ERROR: problem initiating textures\n", data, text);
//    ft_initialize_events(data);
    mlx_loop(data->mlx_conn);
	free_text(text);
	free(text);
	ft_clean_exit(data);
	return (EXIT_SUCCESS);
}

/*int main(void)
{
    void    *mlx_ptr;
    void    *win_ptr;
    t_img   texture;
    int     img_width;
    int     img_height;
    char    *texture_path = "walls/pixgreen.xpm"; // Replace with your texture path

    // Initialize the MiniLibX connection
    mlx_ptr = mlx_init();
    if (!mlx_ptr)
    {
        printf("ERROR: Failed to initialize MLX.\n");
        return (1);
    }

    // Create a window to display the texture
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Texture Test");
    if (!win_ptr)
    {
        printf("ERROR: Failed to create window.\n");
        return (1);
    }

    // Load the texture
    texture.img = mlx_xpm_file_to_image(mlx_ptr, texture_path, &img_width, &img_height);
    if (!texture.img)
    {
        printf("ERROR: Failed to load texture.\n");
        return (1);
    }

    // Display the texture in the window at (0, 0)
    mlx_put_image_to_window(mlx_ptr, win_ptr, texture.img, 0, 0);

    // Keep the window open
    mlx_loop(mlx_ptr);

    // Free the texture after use (not necessary here since we're not exiting the loop)
    mlx_destroy_image(mlx_ptr, texture.img);

    return 0;
}*/