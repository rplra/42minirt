/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:53 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 17:42:18 by rraja-az         ###   ########.fr       */
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

static int	parse_line(char *line, t_parse *file, t_rt *rt)
{
	char	*type;

	file->tokens = tokenize(line);
	if (!file->tokens)
		exit_with_error("Error: No tokens");
	if (file->tokens[0] && file->tokens[0][0] != '#')
	{
		type = file->tokens[0];
		if (!ft_strcmp(type, "A") && ++file->ambient_count > 1)
			return (print_error(file, "Ambient must only be 1", -1, NULL));
		else if (!ft_strcmp(type, "C") && ++file->camera_count > 1)
			return (print_error(file, "Camera must only be 1", -1, NULL));
		else if (!ft_strcmp(type, "L") && ++file->light_count > 1)
			return (print_error(file, "Light must only be 1", -1, NULL));
		else if (parse_scene(file, rt))
			return (1);
	}
	return (0);
}

int	parse_file(int fd, t_parse *file, t_rt *rt)
{
	char	*line;

	ft_bzero(file, sizeof(t_parse));
	line = get_next_line(fd);
	while (line)
	{
		file->line_num++;
		if (parse_line(line, file, rt))
			return (handle_parse_error(fd, line, file));
		free(line);
		free_array(file->tokens);
		line = get_next_line(fd);
	}
	close(fd);
	if (file->line_num == 0)
		return (print_error(NULL, ERROR_FILEEMPTY, -1, NULL));
	if (file->ambient_count < 1 || file->camera_count < 1
		|| file->light_count < 1)
		return (print_error(NULL, ERROR_MISSINGID, -1, NULL));
	return (0);
}

int	open_file(const char *file, t_rt *rt)
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
	if (parse_file(fd, &parse, rt))
		return (1);
	return (0);
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
