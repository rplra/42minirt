/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:39:28 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/27 10:47:57 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define PARAMS_AMBIENT		3
# define PARAMS_CAMERA		4
# define PARAMS_LIGHT		4
# define PARAMS_SPHERE		4
# define PARAMS_PLANE		4
# define PARAMS_CYLINDER	6

typedef struct	s_parse
{
	char		**params;
	int			param_count;
	int			line_num;
	bool		valid;
}				t_parse;


bool	is_rt_file(const char *filename);
void	parse_file(int fd, t_parse *scene);
void	open_file(const char *file);
char	**tokenize_params(char *params);

int		print_error(char *msg);
void	exit_with_error(char *msg);
void	perror_exit(char *perrmsg);

#endif