#include "cub3d.h"
#include <stdio.h>
int parse_textures_and_colors(t_game_data *game,char **file_data)
{
	int i;
	char **array;
	i = 0;
	while(file_data[i])
	{
		if(strncmp(file_data[i], "NO", 2) == 0)
			game->no_texture = ft_strdup(file_data[i] + 3);
		else if(strncmp(file_data[i], "SO", 2) == 0)
			game->so_texture = ft_strdup(file_data[i] + 3);
		else if(strncmp(file_data[i], "WE", 2) == 0)
			game->we_texture = ft_strdup(file_data[i] + 3);
		else if(strncmp(file_data[i], "EA", 2) == 0)
			game->ea_texture = ft_strdup(file_data[i] + 3);
		else if(strncmp(file_data[i], "F", 1) == 0)
		{
			array = ft_split(file_data[i] + 2, ',');
			game->floor_color[0] = ft_atoi(array[0]);
			game->floor_color[1] = ft_atoi(array[1]);
			game->floor_color[2] = ft_atoi(array[2]);
		}
		else if(strncmp(file_data[i], "C", 1) == 0)
		{
			array = ft_split(file_data[i] + 2, ',');
			game->ceiling_color[0] = ft_atoi(array[0]);
			game->ceiling_color[1] = ft_atoi(array[1]);
			game->ceiling_color[2] = ft_atoi(array[2]);
		}			
		i++;
	}
	return 0;
}
