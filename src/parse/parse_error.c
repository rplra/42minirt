/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:05:01 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/19 20:15:16 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_parse_error(int fd, char *line, t_parse *file)
{
	free(line);
	free_array(file->tokens);
	flush_gnl(fd);
	close(fd);
	return (1);
}
