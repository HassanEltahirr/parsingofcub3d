#include "cub3d.h"
#include <stdio.h>
/*
this function is responsible for counting the number of lines in a file
*/
int total_lines(const char *file_path)
{
	int fd;
	int total_lines;
	// char *line = NULL;

	fd = open(file_path, O_RDONLY);
	if(fd == -1)
		return -1;
	total_lines = 0;
	while(get_next_line(fd) > 0)
	{
		total_lines++;
	}
	close(fd);
	return total_lines;
}
/*
This function is responsible for reading the file content and storing it in a 2D array as well as printing it 
*/
char **read_file(const char *file_path)
{
	int fd;
	char **file_content;
	char *line = NULL;
	int i;

	fd = open(file_path, O_RDONLY);
	if(fd == -1)
		return NULL;
	file_content = (char **)calloc(total_lines(file_path) + 1, sizeof(char *));
	if(file_content == NULL)
		return NULL;
	i = 0;
	line  = get_next_line(fd);
	while((line))
	{
		if(line [0] != '\0' && line[0] != '\n')
		{
			file_content[i] = ft_strtrim(ft_strdup(line), WHITESPACES);
			i++;
		}
		line = get_next_line(fd);
	}
	file_content[i] = NULL;
	close(fd);
	return file_content;
}
/*
this function is used to free the memory allocated for the file content
*/
void free_file_content(char **file_content)
{
	int i;

	i = 0;
	while(file_content[i] != NULL)
	{
		free(file_content[i]);
		i++;
	}
	free(file_content);
}