#include "cub3d.h"
#include <stdlib.h>

int parse_our_map(t_game_data *game_data ,char **file_data, int i)
{
	int j;
	int player_found;
	while (file_data[i])
	{
		j = 0;
		while (file_data[i][j])
		{
			if(file_data[i][j] == 'S' || file_data[i][j] == 'N' || file_data[i][j] == 'W' || file_data[i][j] == 'E')
			{
				if(player_found)
				{
					return -1;
				}
				game_data->row = i;
				game_data->coloumn = j;
				game_data->directions = file_data[i][j];
				file_data[i][j] = '0';
				player_found = 1;
			}
			if (file_data[i][j] != '1' && file_data[i][j] != ' ' && file_data[i][j] != '0')
			{
				printf("Error\n");
				return -1;
			}
			j++;
		}
		i++;
	}
	return 0;
}