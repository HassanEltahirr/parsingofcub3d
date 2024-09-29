#include "cub3d.h"
#include <stdlib.h>
int is_row_fully_walls(char *row)
{
	int i;
	i = 0;
	while(row[i])
	{
		if(row[i] != '1' || row[i] != ' ')
		{
			return 1;
		}
		i++;
	}
	return 0;
}
int ismapenclosedbywalls(char **file_data)
{
    int i = 0, j;
    int height = get_map_height(file_data);

    // Validate that the first and last rows are fully walled
    if (!is_row_fully_walls(file_data[0]) || !is_row_fully_walls(file_data[height - 1]))
    {
        printf("Error1\nMap is not enclosed by walls\n");
        return -1;
    }

    i = 1;
    while (i < height - 1) 
    {
		int previous_width = ft_strlen(file_data[i - 1]);
        int width = ft_strlen(file_data[i]);
		int next_width = ft_strlen(file_data[i + 1]);
        j = 1;
        while (j < width - 1)
        {
			if(j >= previous_width || j >= next_width)
			{
				printf("Error\nMap is not enclosed by walls\n");
				return -1;
			}
            if (file_data[i][j] == '0') 
            {
                if (file_data[i - 1][j] != '1' && file_data[i - 1][j] != ' ')  
                {
                    printf("Error\nMap is not enclosed by walls (top)\n");
                    return -1;
                }
                if (file_data[i + 1][j] != '1' && file_data[i + 1][j] != ' ')  
                {
					printf("%d, %d\n",i, j);
					printf("ROW IS %s and its len is %d", file_data[i + 1], j);
                    printf("Error\nMap is not enclosed by walls (bottom)\n");
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
	int i;
	i = 0;
	while(file_data[i])
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
			if(file_data[i][j] == 'S' || file_data[i][j] == 'N' || file_data[i][j] == 'W' || file_data[i][j] == 'E')
			{
				game_data->row = i;
				game_data->coloumn = j;
				game_data->directions = file_data[i][j];
				file_data[i][j] = '0';
				player_found = 1;
			}
			j++;
		}
		i++;
	}
	if (!player_found)
{
    printf("Error: No player found in the map.\n");
    return -1;
}
	if(ismapenclosedbywalls(file_data) == -1)
	{
		return -1;
	}
	game_data->map = file_data;	
	return 0;
}
