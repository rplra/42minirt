/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:39:28 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/12 14:38:06 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "scene.h"

# define PARAMS_AMBIENT		3
# define PARAMS_CAMERA		4
# define PARAMS_LIGHT		4
# define PARAMS_SPHERE		4
# define PARAMS_PLANE		4
# define PARAMS_CYLINDER	6

typedef struct	s_parse
{
	char		**tokens;
	int			param_count;
	int			ambient_count;
	int			camera_count;
	int			light_count;
	int			line_num;
	bool		valid;
}				t_parse;

/*		parse_file.c		*/
bool	is_rt_file(const char *filename);
int		parse_file(int fd, t_parse *file, t_scene *scene);
int		open_file(const char *file, t_scene *scene);
char	**tokenize(char *line);

/*		parse_scene.c		*/
int		parse_scene(t_parse *file, t_scene *scene);
int		parse_object(t_parse *file, t_scene *scene);

/*		parse_setup.c		*/
int		parse_ambient(char **params, t_parse *file, t_ambient *ambient);
int		parse_camera(char **params, t_parse *file, t_camera *camera);
int		parse_light(char **params, t_parse *file, t_light *light);

/*		parse_objects.c		*/
int		parse_plane(t_parse *file, t_object *obj);
int 	parse_sphere(t_parse *file, t_object *obj);
int		parse_cylinder(t_parse *file, t_object *obj);

/*		parse_utils.c		*/
bool	is_object(const char *token);
int		add_object(t_scene *scene, t_object obj);
int		count_params(char **params);
int		is_colour(t_parse *scene, char **col, t_colour *colour);
int		is_vector(t_parse *scene, char **values, t_vector *vector, bool check_normal);

/*		parse_debug.c		*/
void	print_ambient(const t_ambient *ambient);
void 	print_camera(const t_camera *camera);
void 	print_light(const t_light *light);
void 	print_plane(const t_object *obj);
void	print_sphere(const t_object *obj);
void	print_cylinder(const t_object *obj);

#endif