/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:53 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/28 09:36:48 by rraja-az         ###   ########.fr       */
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
void	parse_file(int fd, t_parse *scene)
{
	char	*line;

	scene->line_num = 0;
	scene->valid = 1;
	line = get_next_line(fd);
	while (line)
	{
		scene->line_num++;
		scene->tokens = tokenize(line);
		//if (parse_params(line))
		//	scene->valid = 0;
		// print params
/* 		if (scene->tokens)
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
		free(line);
		free(scene->tokens);
		line = get_next_line(fd);
	}
}

void	open_file(const char *file)
{
	int		fd;
	t_parse	scene;

	if (!is_rt_file(file))
		exit_with_error("Error: File must in .rt format");
	if (access(file, F_OK | R_OK) < 0)
		exit_with_error("Error: File does not exist or has no read permission");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error: File not found");
	parse_file(fd, &scene);
	if (scene.line_num == 0)
		exit_with_error("Error: Empty file");
	close(fd);
}

char	**tokenize(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\t' || input[i] == '\n')
			input[i] = ' ';
	}
	return (ft_split(input, ' '));
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