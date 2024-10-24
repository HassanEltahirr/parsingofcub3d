#include "cub3d.h"
int	set_flag(int *flag, char *identifier)
{
	if (*flag)
	{
		printf("Error: Duplicate '%s' definition.\n", identifier);
		return (-1);
	}
	*flag = 1;
	return (0);
}

int	check_identifiers(char *line, int *flags)
{
	if (ft_strncmp(line, "NO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (set_flag(&flags[0], "NO"));
	else if (ft_strncmp(line, "SO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (set_flag(&flags[1], "SO"));
	else if (ft_strncmp(line, "WE", 2) == 0 && 		(line[2] == ' ' || line[2] == '\t'))
		return (set_flag(&flags[2], "WE"));
	else if (ft_strncmp(line, "EA", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		return (set_flag(&flags[3], "EA"));
	else if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (set_flag(&flags[4], "F"));
	else if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (set_flag(&flags[5], "C"));
	return (0);
}

int	check_missing_identifiers(int *flags)
{
	const char	*ids[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (!flags[i])
		{
			printf("Error: Missing '%s' definition.\n", ids[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	validate_file_content(char **file_data)
{
	int		i =0;
	int		flags[6];
	char	*trimmed_line;
	char **split_line;
	if(file_data[i] == NULL)
	{
		printf("Error: Empty file.\n");
		return (-1);
	}
	split_line = ft_split(file_data[0], '\n');
	i = 0;
	ft_bzero(flags, sizeof(flags));
	
	while (file_data[i])
	{
		trimmed_line = ft_strtrim(file_data[i], " \t\n");
		if (trimmed_line[0] != '\0')
		{
			if (check_identifiers(trimmed_line, flags) == -1)
			{
				free(trimmed_line);
				return (-1);
			}
		}
		free(trimmed_line);
		i++;
	}
	if (check_missing_identifiers(flags) == -1)
		return (-1);
	return (0);
}
