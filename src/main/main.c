/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:09:38 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/27 11:14:10 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test_file_functions(const char *filepath);

int main(int ac, char **av)
{
	char	*filepath;
	
	if (ac != 2)
		exit_with_error(ERROR_ARGFORMAT);
	filepath = av[1];
	test_file_functions(filepath);
	// open file
	// run mlx
	// clean
	return (0);
}

void	test_file_functions(const char *filepath)
{
    printf("Testing file: %s\n", filepath);

    if (!is_rt_file(filepath))
    {
        printf("is_rt_file: FAIL (not .rt extension)\n");
        return;
    }
    else
        printf("is_rt_file: PASS\n");

    if (access(filepath, F_OK | R_OK) < 0)
    {
        printf("access: FAIL (file missing or unreadable)\n");
        return;
    }
    else
        printf("access: PASS\n");

    int fd = open(filepath, O_RDONLY);
    if (fd < 0)
    {
        printf("open: FAIL (could not open file)\n");
        return;
    }
    else
        printf("open: PASS\n");
	
    t_parse scene;
    parse_file(fd, &scene);
    close(fd);

    if (scene.line_num == 0)
        printf("parse_file: FAIL (empty file)\n");
    else if (scene.valid == 0)
        printf("parse_file: FAIL (invalid content)\n");
    else
        printf("parse_file: PASS\n");

	
}
