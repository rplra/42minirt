/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:53 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/26 18:24:24 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_rt_file(const char *filename)
{
	int	len;
	
	len = ft_strlen(filename);
	if (len > 3 && ft_strcmp(filename + len - 3, ".rt") == 0)
		return (true);
	return (false);
}

// read file

void	open_file(const char *file)
{
	int	fd;

	if (!is_rt_file(file))
		exit_with_error("Error: File must in .rt extension");
	if (access(file, F_OK | R_OK) < 0)
		exit_with_error("Error: File does not exist or has no read permission");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error: File not found");
	read_file(file);
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