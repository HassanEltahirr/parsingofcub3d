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
	t_game_data game_data = {0};
	char **file_content;

	file_content = read_file(file_path);
	if(file_content == NULL)
		return -1;
	if(parse_textures_and_colors(&game_data, file_content) == -1)
	{
		free_file_content(file_content);
		return -1;
	}
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