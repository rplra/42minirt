/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:53 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/27 09:54:01 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_rt_file(const char *filename)
{
	int	len;
	
	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len > 3 && ft_strcmp(filename + len - 3, ".rt") == 0)
		return (true);
	return (false);
}

void	parse_file(int fd, const char *filepath, t_parse *scene)
{
	char	*line;

	scene->line_num = 0;
	scene->valid = 1;
	line = getnextline(fd);
	while (line)
	{
		scene->line_num++;
		scene->params = tokenize_params(line);
		if (parse_params(line))
			scene->valid = 1;
		free(line);
	}
}

void	open_file(const char *file)
{
	int		fd;
	t_parse	scene;

	if (!is_rt_file(file))
		exit_with_error("Error: File must in .rt extension");
	if (access(file, F_OK | R_OK) < 0)
		exit_with_error("Error: File does not exist or has no read permission");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error: File not found");
	parse_file(fd, file, &scene);
	close(fd);
}

char	**tokenize_params(char *params)
{
	int	i;

	i = -1;
	while (params[++i])
	{
		if (params[i] == '\t' || params[i] == '\n')
			params[i] = ' ';
	}
	return (ft_split(params, ' '));
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