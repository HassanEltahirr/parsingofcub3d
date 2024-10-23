#include "cub3d.h"
#include <stdio.h>

int total_lines(const char *file_path)
{
	int	fd;
	int	total_lines;

	fd = open(file_path, O_RDONLY);
	if(fd == -1)
		return -1;
	total_lines = 0;
	while(get_next_line(fd) > 0)
		total_lines++;
	close(fd);
	return (total_lines);
}
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
	while(line)
	{
			file_content[i] = ft_strdup(line);
			i++;
			line = get_next_line(fd);
	}
	file_content[i] = NULL;
	close(fd);
	return (file_content);
}
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