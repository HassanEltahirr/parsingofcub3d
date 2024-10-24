#include "cub3d.h"
#include <stdlib.h>
int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}
int ismapenclosedbywalls(char **file_data)
{
    int i = 0;
    int j;
    int height = get_map_height(file_data);

    i = 0;
    while (i < height) 
    {
        int width = ft_strlen(file_data[i]);
        int widthlinebefore = ft_strlen(file_data[i - 1]);
        // int widthlineafter = ft_strlen(file_data[i + 1]);
        j = 0;
        while (j < width && is_valid_char(file_data[i][j]))
        {
            if (file_data[i][j] == '0' || file_data[i][j] == 'N' || file_data[i][j] == 'S' || file_data[i][j] == 'E' || file_data[i][j] == 'W')
            {
                if(width > widthlinebefore  || width < widthlinebefore)
            {
                printf("Error\nMap is not enclosed by walls (top or bottom edge)\n");
                return -1;
            }
                if (j == 0 || j == width - 1)
                {
                    printf("Error\nMap is not enclosed by walls (left or right edge)\n");
                    return -1;
                }
                if (!is_valid_char(file_data[i - 1][j]))
                {
                    printf("Error\nMap is not enclosed by walls (top of position [%d][%d])\n", i, j);
                    return -1;
                }
                if (!is_valid_char(file_data[i + 1][j]))
                {
                    printf("Error\nMap is not enclosed by walls (bottom of position [%d][%d])\n", i, j);
                    return -1;
                }
                if (!is_valid_char(file_data[i][j - 1]))
                {
                    printf("Error\nMap is not enclosed by walls (left of position [%d][%d])\n", i, j);
                    return -1;
                }
                if (!is_valid_char(file_data[i][j + 1]))
                {
                    printf("Error\nMap is not enclosed by walls (right of position [%d][%d])\n", i, j);
                    return -1;
                }
            }
            j++;
        }
        i++;
    }
    return 0;
}

int get_map_height(char **file_data)
{
    int i = 0;
    while (file_data[i])
    {
        i++;
    }
    return i;
}

int parse_our_map(t_game_data *game_data ,char **file_data, int i)
{
    int j;
    int player_found = 0;
    i = 0;
    while (file_data[i])
    {
        if(file_data[i][1] == '\0')
        {
            printf("Error: Blank line detected at line %d.\n", i + 1);
            return -1;
        }
        j = 0;
        while (file_data[i][j])
        {
            if (ft_strchr("SNWEPD", file_data[i][j]) &&  player_found == 0)
            {
                game_data->row = i;
                game_data->coloumn = j;
                game_data->directions = file_data[i][j];
                file_data[i][j] = '0';  
                player_found++;
            }
            else if(!ft_strchr("01NSEW \n", file_data[i][j]))
            {
                printf("Error: Invalid character in map.\n");
                return -1;
            }
            j++;
        }
        i++;
    }
    if (player_found != 1)
    {
        printf("Error with player found in the map.\n");
        return -1;
    }
    if (ismapenclosedbywalls(file_data) == -1)
    {
        return -1;
    }
    game_data->map = file_data;
    return 0;
}