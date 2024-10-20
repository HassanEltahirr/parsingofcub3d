#include "cub3d.h"
#include <stdlib.h>

int is_row_fully_walls(char *row)
{
    int i = 0;
    while (row[i])
    {
        if (row[i] != '1' && row[i] != ' ' && row[i] != '\n')
        {
            printf("%c",row[i]);
            return 1;  // Return 1 (error) if the row contains something other than '1' or ' '
        }
        i++;
    }
    return 0;
}
int is_valid_char(char c)
{
    // Valid characters adjacent to '0' are '0', '1', and player positions
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}
int ismapenclosedbywalls(char **file_data)
{
    int i = 0, j;
    int height = get_map_height(file_data);

    // Validate that the first and last rows are fully walled
    if (is_row_fully_walls(file_data[0]) || is_row_fully_walls(file_data[height - 1]))
    {
        printf("Error\nMap is not enclosed by walls (top or bottom row)\n");
        return -1;
    }
    i = 1;
    while (i < height - 1) 
    {
        int width = ft_strlen(file_data[i]);
        j = 0;
        while (j < width && is_valid_char(file_data[i][j]))
        {
            if (file_data[i][j] == '0' || file_data[i][j] == 'N' || file_data[i][j] == 'S' || file_data[i][j] == 'E' || file_data[i][j] == 'W')
            {
                // Check for out-of-bounds
                if (j == 0 || j == width - 1)
                {
                    printf("Error\nMap is not enclosed by walls (left or right edge)\n");
                    return -1;
                }

                // Check surrounding characters
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
        j = 0;
        while (file_data[i][j])
        {
            if(file_data[i][j] == ' ')
            {
                file_data[i][j] = '1';
            }
            if (file_data[i][j] == 'S' || file_data[i][j] == 'N' || file_data[i][j] == 'W' || (file_data[i][j] == 'E' && player_found == 0))
            {
                game_data->row = i;
                game_data->coloumn = j;
                game_data->directions = file_data[i][j];
                file_data[i][j] = '0';  // Replace player position with '0'
                player_found++;
            }
            else if(!(file_data[i][j] == '0' || file_data[i][j] == '1' || file_data[i][j] == 'N' || file_data[i][j] == 'S' || file_data[i][j] == 'E' || file_data[i][j] == 'W' || file_data[i][j] == ' ' || file_data[i][j] == '\n'))
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
