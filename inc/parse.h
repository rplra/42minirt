/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:39:28 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/22 17:31:29 by rraja-az         ###   ########.fr       */
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
	char		**tokens;
	int			token_count;
	int			line_num;
}				t_parse;


#endif