#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"

char **read_file(const char *file_path);

int is_texture_or_color_line(char *line)
{
    char *trimmed = ft_strtrim(line, " \t\r");
    if (!trimmed)
    {
        fprintf(stderr, "Error: Memory allocation failed during trimming.\n");
        return 0;
    }
    if (ft_strncmp(trimmed, "NO ", 3) == 0 ||
        ft_strncmp(trimmed, "SO ", 3) == 0 ||
        ft_strncmp(trimmed, "WE ", 3) == 0 ||
        ft_strncmp(trimmed, "EA ", 3) == 0 ||
        ft_strncmp(trimmed, "S ", 2) == 0)
    {
        if(trimmed[2] != ' ')
        {
            printf("Error: Invalid character in texture line.\n");
            free(trimmed);
            return -1;
        }
        free(trimmed);
        return 1;
    }

    // Check for color lines: "F " and "C "
    if (ft_strncmp(trimmed, "F ", 2) == 0 ||
        ft_strncmp(trimmed, "C ", 2) == 0)
    {
        if(trimmed[1] != ' ')
        {
            printf("Error: Invalid character in color line.\n");
            free(trimmed);
            return -1;
        }
        free(trimmed);
        return 1;
    }

    free(trimmed);
    return 0;
}

int find_map_start(char **file_data)
{
    int i = 0;
    while (file_data[i])
    {
        char *trimmed = ft_strtrim(file_data[i], " \t\n\r");
        if (!trimmed)
        {
            write(3,"Error: Memory allocation failed during trimming.\n", 49);
        }
        if (trimmed[0] == '\0')
        {
            free(trimmed);
            i++;
            continue;
        }
        if (is_texture_or_color_line(trimmed))
        {
            free(trimmed);
            i++;
            continue;
        }
        if (is_texture_or_color_line(trimmed) == -1)
        {
            write(1,"Error: Invalid character in texture or color line.\n", 51);
            free(trimmed);
            return -1;
        }

        if (ft_strchr(trimmed, '1') || ft_strchr(trimmed, '0'))
        {
            free(trimmed);
            return i;
        }
        free(trimmed);
        i++;
    }
    return -1;
}
void init_game_data(t_game_data *game_data)
{
    *game_data = (t_game_data){0};
    game_data->floor_color[0] = -1;
    game_data->floor_color[1] = -1;
    game_data->floor_color[2] = -1;
    game_data->ceiling_color[0] = -1;
    game_data->ceiling_color[1] = -1;
    game_data->ceiling_color[2] = -1;
}
int checkforblanklines(char **file_data)
{
    int i = 0;
    while (file_data[i])
    {
        if(file_data[i][0] == '\0')
        {
            printf("Error: Blank line detected at line %d.\n", i + 1);
            return -1;
        }
        i++;
    }
    return 0;
}
int parse_cub_file(const char *file_path)
{
    char        **file_content;
    t_game_data game_data;
    int         w;
  
	init_game_data(&game_data);
    file_content = read_file(file_path);
    if(file_content == NULL)
    {
        return printf("Error: The file wasn't found.\n"), -1;
    }
    if(validate_file_content(file_content) == -1)
                return free_file_content(file_content),-1;
    if(parse_textures_and_colors(&game_data, file_content) == -1)
                return free_file_content(file_content),-1;
    w = find_map_start(file_content);
    if (w == -1)
    {
        printf("Error: No valid map found in the file.\n");
        	return free_file_content(file_content),-1;
    }
    if (parse_our_map(&game_data, &file_content[w], w) == -1)
        return free_file_content(file_content),-1;
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
	
	if(ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		printf("Error the name is incorrect \n");
		return -1;
	}
	if(parse_cub_file(av[1]) == -1)
	{
		return -1;
	}
}