/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbolon <kbolon@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:42:05 by kbolon            #+#    #+#             */
/*   Updated: 2024/09/04 16:38:40 by kbolon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	valid_chars(t_textinfo *text)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (text->grid[i] != NULL)
	{
		j = 0;
		while (text->grid[i][j] != '\0')
		{
			if (ft_strchr("01NSEW \t\n", text->grid[i][j]))
				j++;
			else
				error_message_text("ERROR: illegal character in map\n", text);
		}
		i++;
	}
}

void	count_chars(char **arr, size_t *player)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			if (arr[i][j] == 'N' || arr[i][j] == 'S' || \
				arr[i][j] == 'W' || arr[i][j] == 'E')
				(*player) += 1;
			j++;
		}
		i++;
	}
}

void	check_map_items(t_textinfo *text)
{
	size_t		player;

	player = 0;
	count_chars(text->grid, &player);
	if (player != 1)
		error_message_text("ERROR: Too many players, check content\n", text);
}

//this function has been tailored for cub3d
int	ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (0);
	while ((str[i] != '\0') && (to_find[j] != '\0'))
	{
		while (str[i + j] == to_find[j] && str[i + j] != '\0')
			j++;
		if (to_find[j] == '\0')
			return (1);
		i++;
		j = 0;
	}
	return (0);
}

char	*ft_trim_line(char *str)
{
	while (*str== ' ' || *str == '\t')
			str++;
	return (str);
}
