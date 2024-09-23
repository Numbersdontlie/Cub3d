#include "../includes/cub3D.h"

int on_destroy(t_data *data)
{
	if (data->textures[0])
		mlx_destroy_image(data->mlx_conn, data->textures[0]);
	if (data->mlx_window)
		mlx_destroy_window(data->mlx_conn, data->mlx_window);
	mlx_loop_end(data->mlx_conn);
	if (data->mlx_conn)
	{
		mlx_destroy_display(data->mlx_conn);
		free(data->mlx_conn);
	}
	exit(0);
	return (0);
}

int on_keypress(int keysym, t_data *data)
{
	printf("Pressed key: %d\n", keysym);
	if (keysym == 65307) // Escape key to close the window
	{
		on_destroy(data);  // Close window on ESC key press
	}
	return (0);
}

int main(void)
{
	t_data  data;
	char	*path;

//	path = "walls/temple.xpm";
	path = "walls/pixgreen.xpm";

	data.mlx_conn = mlx_init();
	if (!data.mlx_conn)
		return (1);
	data.mlx_window = mlx_new_window(data.mlx_conn, WIDTH, HEIGHT, "hi :)");
	if (!data.mlx_window)
	{
		mlx_destroy_display(data.mlx_conn);
		free(data.mlx_conn);
		return (1);
	}
	data.textures[0] = mlx_xpm_file_to_image(data.mlx_conn, path, &data.image_width, &data.image_height);
	if (!data.textures[0])
	{
		printf("Error loading texture: %s\n", path);
		mlx_destroy_window(data.mlx_conn, data.mlx_window);
		mlx_destroy_display(data.mlx_conn);
		free(data.mlx_conn);
		return (1);		
	}
	mlx_put_image_to_window(data.mlx_conn, data.mlx_window, data.textures[0], 0, 0);
	mlx_hook(data.mlx_window, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	mlx_loop(data.mlx_conn);
	if (data.mlx_conn)
	{
		mlx_destroy_display(data.mlx_conn);
		free(data.mlx_conn);
	}
	return (0);
}