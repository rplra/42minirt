/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:53 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/05 14:03:47 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_rt_file(const char *filename)
{
	int	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len > 3 && ft_strncmp(filename + len - 3, ".rt", 3) == 0)
		return (true);
	return (false);
}

// to check if there are invalid params, interrupt gnl and free line
void	parse_file(int fd, t_parse *file)
{
	char	*line;
	t_scene	scene;

	file->ambient_count = 0;
	file->camera_count = 0;
	file->light_count = 0;
	file->line_num = 0;
	line = get_next_line(fd);
	while (line)
	{
		file->tokens = tokenize(line);
		file->line_num++;
		if (file->tokens && file->tokens[0])
		{
			if (ft_strcmp(file->tokens[0], "A") == 0)
				file->ambient_count++;
			else if (ft_strcmp(file->tokens[0], "C") == 0)
				file->camera_count++;
			else if (ft_strcmp(file->tokens[0], "L") == 0)
				file->light_count++;
		}
		if (!parse_scene(file, &scene))
			exit(1);
		//print_scene(&scene);
		free(line);
		free(file->tokens);
		line = get_next_line(fd);
	}
	validate_setup(file);
}

void	open_file(const char *file)
{
	int		fd;
	t_parse	scene;

	if (!is_rt_file(file))
		exit_with_error(ERROR_FILETYPE);
	if (access(file, F_OK | R_OK) < 0)
		exit_with_error(ERROR_FILEMOD);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_with_error(ERROR_FILEFD);
	parse_file(fd, &scene);
	if (scene.line_num == 0)
		exit_with_error(ERROR_FILEEMPTY);
	close(fd);
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