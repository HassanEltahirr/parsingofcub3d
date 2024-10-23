#include "cub3d.h"
#include <stdio.h>
int free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}
int use_atoi(t_game_data *game, char **split_color, char texture)
{
    int color[3];

    color[0] = ft_atoi(split_color[0]);
    color[1] = ft_atoi(split_color[1]);
    color[2] = ft_atoi(split_color[2]);
    if (color[0] < 0 || color[0] > 255 
        || color[1] < 0 || color[1] > 255 
        || color[2] < 0 || color[2] > 255)
        return (0);
    if (texture == 'F')
    {
        game->floor_color[0] = color[0];
        game->floor_color[1] = color[1];
        game->floor_color[2] = color[2];
    }
    else if (texture == 'C')
    {
        game->ceiling_color[0] = color[0];
        game->ceiling_color[1] = color[1];
        game->ceiling_color[2] = color[2];
    }
    else
        return (0);
    return (1);
}

int set_texture(t_game_data *game, char *texture)
{
    char    **split;
    int     result = 0;

    split = ft_split(texture, ' ');
    if (!split || !split[0] || !split[1] || split[2] || ft_strlen(split[0]) != 2)
    {
        free_split(split);
        return (0);
    }
    if (ft_strcmp(split[0], "NO") == 0 && !game->no_texture)
    {
        game->no_texture = ft_strdup(split[1]);
        result = 1;
    }
    else if (ft_strcmp(split[0], "SO") == 0 && !game->so_texture)
    {
        game->so_texture = ft_strdup(split[1]);
        result = 1;
    }
    else if (ft_strcmp(split[0], "WE") == 0 && !game->we_texture)
    {
        game->we_texture = ft_strdup(split[1]);
        result = 1;
    }
    else if (ft_strcmp(split[0], "EA") == 0 && !game->ea_texture)
    {
        game->ea_texture = ft_strdup(split[1]);
        result = 1;
    }
    free_split(split);
    return result;
}
char *remove_all_spaces(char *str)
{
    char *new_str;
    int i;
    int j;

    i = 0;
    j = 0;
    new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!new_str)
        return (NULL);
    while (str[i])
    {
        if (str[i] != ' ')
        {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';
    return (new_str);
}
int validatenumberofargs(char **split_color)
{
    int i = 0;
    while (split_color[i])
    {
        int j = 0;
        while (split_color[i][j])
        {
            if (!ft_isdigit(split_color[i][j]))
                // printf("%c", split_color[i][j]);
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}
char **split_with_color(char *s)
{
    int i = 0;
    int flag;

    flag = 0;
    while (s[i] == ' ')
        i++;
    if (s[i] == 'F' || s[i] == 'C')
    {
        i++;
        while (s[i] == ' ' && flag++)
            i++;
    }
    if (flag != 1)
        return NULL;
    return ft_split(s + i, ',');
}
int set_color(t_game_data *game, char *texture)
{
    char **split_str;
    char **split_color;
    int result = 0;
    int checker = 0;
    split_color = split_with_color(texture);
    if (!split_color || !split_color[0] || !split_color[1] || !split_color[2] || split_color[3])
    {
        printf("Error: Invalid color identifier\n");
        free_split(split_color);
        return (0);
    }
    split_str = ft_split(texture, ' ');
    if (ft_strcmp(split_str[0], "F") == 0 && game->floor_color[0] == -1)
    {
        result = use_atoi(game, split_color, 'F');
        checker++;
    }
    else if (ft_strcmp(split_str[0], "C") == 0 )
    {
        result = use_atoi(game, split_color, 'C');
    }
    else
    {
        printf("Error: Unknown color identifier\n");
        result = 0;
    }
    free_split(split_str);
    free_split(split_color);

    return result;
}

int parse_textures_and_colors(t_game_data *game, char **file_data)
{
    int  i;
    char **split;
    i = 0;
    while (file_data[i] && file_data[i][0] != '1')
    {
        split = ft_split(file_data[i], ' ');
        if (!split || !split[0])
        {
            free_split(split);
            i++;
            continue;
        }
        if (ft_strcmp(split[0], "NO") == 0 || ft_strcmp(split[0], "SO") == 0 ||
            ft_strcmp(split[0], "WE") == 0 || ft_strcmp(split[0], "EA") == 0)
        {
            if (!set_texture(game, file_data[i]))
            {
                printf("Error: Failed to set texture for %s\n", split[0]);
                free_split(split);
                return (-1);
            }
        }
        else if (ft_strcmp(split[0], "F") == 0 || ft_strcmp(split[0], "C") == 0)
        {
            if (!set_color(game, file_data[i]))
            {
                printf("Error: Failed to set color for %s\n", split[0]);
                free_split(split);
                return (-1);
            }
        }
        free_split(split);
        if (game->no_texture && game->so_texture && game->we_texture && game->ea_texture)
            game->is_texture_set = 1;
        if (game->floor_color[0] != -1 && game->floor_color[1] != -1 && game->floor_color[2] != -1
            && game->ceiling_color[0] != -1 && game->ceiling_color[1] != -1 && game->ceiling_color[2] != -1)
            game->is_color_set = 1;     
        i++;
    }
    return 0;
}
