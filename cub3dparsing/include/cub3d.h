#ifndef CUB3D_H
#define CUB3D_H
#define WHITESPACES "\n\r\v\f \t 32"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../getnextline/get_next_line.h"
#include "../libft/libft.h"
typedef struct s_game_data
{
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	char *sprite_texture;
	int floor_color[3];
	int ceiling_color[3];
	char **map;
	int row;
	int coloumn;
	char directions;
	int	is_texture_set;
	int	is_color_set;
}t_game_data;
char **read_file(const char *file_path);
void free_file_content(char **file_content);
int parse_cub_file(const char *file_path);
int parse_textures_and_colors(t_game_data *game,char **file_data);
char				**ft_split(char const *s, char c);
int parse_our_map(t_game_data *game_data ,char **file_data, int i);
int get_map_height(char **file_data);
int finalize_map(t_game_data *game_data,char **file_data);

#endif
