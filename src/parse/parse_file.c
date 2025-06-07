/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:53 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/07 10:49:57 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_rt_file(const char *filename)
{
	int	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	return ((len >= 3 && !ft_strncmp(filename + len - 3, ".rt", 3)));
}

static void	parse_line(char *line, t_parse *file, t_scene *scene)
{
	char	*type;

	file->tokens = tokenize(line);
	//for (int i = 0; file->tokens && file->tokens[i] ; i++) // debug
	//		printf("   Line: %d, Token %d: [%s]\n", file->line_num, i, file->tokens[i]); // debug
	if (!file->tokens)
		exit_with_error("Error: No tokens");
	if (file->tokens[0] && file->tokens[0][0] != '#')
	{
		type = file->tokens[0];
		if (!ft_strcmp(type, "A") && ++file->ambient_count > 1)
			exit_with_error("Error: Ambient must only be 1");
		else if (!ft_strcmp(type, "C") && ++file->camera_count > 1)
			exit_with_error("Error: Camera must only be 1");
		else if (!ft_strcmp(type, "L") && ++file->light_count > 1)
			exit_with_error("Error: Light must only be 1");
		else if (parse_scene(file, scene))
			exit(1);
	}
}

// to check if there are invalid params, interrupt gnl and free line
void	parse_file(int fd, t_parse *file, t_scene *scene)
{
	char	*line;

	ft_bzero(file, sizeof(t_parse));
	while ((line = get_next_line(fd)))
	{
		//printf("\n-->Line: %s\n", line); // debug
		file->line_num++;
		parse_line(line, file, scene);
		free(line);
		free_array(file->tokens);
	}
	close(fd);
	if (file->line_num == 0)
		exit_with_error(ERROR_FILEEMPTY);
	if (file->ambient_count < 1 || file->camera_count < 1
		|| file->light_count < 1)
		exit_with_error(ERROR_MISSINGID);
}

void	open_file(const char *file, t_scene *scene)
{
	int		fd;
	t_parse	parse;

	if (!is_rt_file(file))
		exit_with_error(ERROR_FILETYPE);
	if (access(file, F_OK | R_OK) < 0)
		exit_with_error(ERROR_FILEMOD);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_with_error(ERROR_FILEFD);
	parse_file(fd, &parse, scene);
}

char	**tokenize(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\t' || line[i] == '\n')
			line[i] = ' ';
	}
	return (ft_split(line, ' '));
}

/*
	FILE.C

	1. validate file
		- extension .rt
		- read permission > error n exit
		- open file
			- empty file
	
	2. validate args
		- check all params have exact count / not empty
		- check all inputs are ints/floats/doubles only 
		- check all params are within bounds
		- check for valid vector format (3-comma seperated floats)
		- check for normalized vector

	3. semantic checks
		- no duplicates of A, R, C
		- check object bounds
*/

		// print params
		/* 	if (scene->tokens)
        {
            int i = 0;
            printf("tokens:");
            while (scene->tokens[i])
            {
                printf(" [%s]", scene->tokens[i]);
                i++;
            }
            printf("\n");
        }  */

		
/* void	parse_file(int fd, t_parse *file, t_scene *scene)
{
	char	*line;

	file->ambient_count = 0;
	file->camera_count = 0;
	file->light_count = 0;
	file->line_num = 0;
	line = get_next_line(fd);
	while (line)
	{
		file->tokens = tokenize(line);
		for (int i = 0; file->tokens && file->tokens[i] ; i++) // debug
			printf("  Line: %d, Token %d: [%s]\n", file->line_num, i, file->tokens[i]); // debug
		file->line_num++;
		if (file->tokens && file->tokens[0] && file->tokens[0][0] != '#')
		{
			if (ft_strcmp(file->tokens[0], "A") == 0)
				file->ambient_count++;
			else if (ft_strcmp(file->tokens[0], "C") == 0)
				file->camera_count++;
			else if (ft_strcmp(file->tokens[0], "L") == 0)
				file->light_count++;
		}
		//printf("parse scene\n"); // debug
		if (!parse_scene(file, scene))
		{
			free(line);
			free_array(file->tokens);
			close(fd);
			exit(1);
		}
		line = get_next_line(fd); //debug
		printf("%s", line);
	}
	if (file->line_num == 0)
		exit_with_error(ERROR_FILEEMPTY);
	validate_setup(file);
	close(fd);
} */