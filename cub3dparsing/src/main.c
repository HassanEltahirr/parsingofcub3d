#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"

char **read_file(const char *file_path);

void free_file_content(char **file_content);
/*
	this function is responsible for parsing the cub file
*/
int parse_cub_file(const char *file_path)
{
	char		**file_content;
	t_game_data	game_data;
	int 		i;

	game_data = (t_game_data){0};
	game_data.floor_color[0] = -1;
	game_data.floor_color[1] = -1;
	game_data.floor_color[2] = -1;
	game_data.ceiling_color[0] = -1;
	game_data.ceiling_color[1] = -1;
	game_data.ceiling_color[2] = -1;
	file_content = read_file(file_path);
	if(file_content == NULL)
		return -1;
	char **trimmed_line = NULL;
	trimmed_line = file_content;
	i = 0;
	file_content[i] = ft_strdup(*trimmed_line);
	if(parse_textures_and_colors(&game_data, file_content) == -1)
	{
		free_file_content(file_content);
		return -1;
	}
	while(file_content[i][0] != '1')
			i++;
	parse_our_map(&game_data,&file_content[i], i);
	free_file_content(file_content);
	return 0;
}
int main(int ac,char **av)
{
	if(ac != 2)
	{
		printf("Usage: ./cub3d_parser <path_to_cub_file>\n");
		return 0;	
	}	
	if(parse_cub_file(av[1]) == -1)
	{
		printf("Error\n");
		return -1;
	}
}