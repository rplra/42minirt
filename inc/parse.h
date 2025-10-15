/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:39:28 by rraja-az          #+#    #+#             */
/*   Updated: 2025/10/14 21:31:41 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "scene.h"

# define TOKENS_AMBIENT 	3
# define TOKENS_CAMERA 		4
# define TOKENS_LIGHT 		4
# define TOKENS_SPHERE 		4
# define TOKENS_PLANE 		4
# define TOKENS_CYLINDER	6

# define ERROR_ARGFORMAT "Format: <./minirt> <scenes/scene.rt>"
# define ERROR_FILETYPE "Error: File type must be in .rt"
# define ERROR_FILEMOD "File does not exist or has no read permission"
# define ERROR_FILEFD "File not found"
# define ERROR_FILEEMPTY "Empty file"
# define ERROR_PARAMEMPTY "Empty parameter"
# define ERROR_INVALIDID "ID must be valid [A] [C] [L] [pl] [sp] [cy]"

# define ERROR_UNIQUEID "A, C, L should be unique"
# define ERROR_MISSINGID "Scene must at least have one A, C and L to render"
# define ERROR_RATIO "Invalid ratio, range must be within 0.0 to 1.0"
# define ERROR_NORMAL "Invalid vector normal"
# define ERROR_VECTOR "Vector value must be -1 to 1"

# define ERROR_ACOUNT "Ambient params must be 3 [A, light ratio, colour]"

# define ERROR_CCOUNT "Camera params: 4 [C, coords, orientation, FOV]"
# define ERROR_CPOS "Invalid camera position"
# define ERROR_CORT "Invalid camera orientation"
# define ERROR_CFOV "Camera FOV must be between 0 to 180"

# define ERROR_LCOUNT "Light params: 4 [L, coords, brightness, colour]"
# define ERROR_LPOS "Invalid Light position"

# define ERROR_PLCOUNT "Plane params must be 4 [pl, coords, normal, colour]"
# define ERROR_PLPOS "Invalid Plane position"
# define ERROR_PLORT "Invalid Plane orientation"

# define ERROR_SPCOUNT "Sphere params: 4 [sp, coords, diameter, colour]"
# define ERROR_SPPOS "Invalid Sphere position"
# define ERROR_SPDIA "Sphere diameter must be a positive interger"

# define ERROR_CYCOUNT "Cylinder params: 6 [cy, coords, axis, dia, ht, col]"
# define ERROR_CYPOS "Invalid Cylinder position"
# define ERROR_CYDIA "Cylinder diameter must be a positive integer"
# define ERROR_CYHT "Cylinder height must be a positive integer"

# define ERROR_COLCOUNT "Colour must consist of 3 values [R, G, B]"
# define ERROR_INVALID_R "R colour value must be a positive integer [0 to 255]"
# define ERROR_INVALID_G "G colour value must be a positive integer [0 to 255]"
# define ERROR_INVALID_B "B colour value must be a positive integer [0 to 255]"
# define ERROR_INVALID_COL_VAL "Colour values must be 0 to 255"

# define ERROR_INVALID_COORD "Coordinate must consist of 3 values; x, y, z"
# define ERROR_INVALID_X "X value must be an integer"
# define ERROR_INVALID_Y "Y value must be an integer"
# define ERROR_INVALID_Z "Z value must be an integer"

typedef struct s_rt	t_rt;

typedef struct s_parse
{
	char			**tokens;
	int				param_count;
	int				ambient_count;
	int				camera_count;
	int				light_count;
	int				line_num;
	bool			valid;
}					t_parse;

/*					parse_file.c				*/
bool				is_rt_file(const char *filename);
int					parse_file(int fd, t_parse *file, t_rt *rt);
int					open_file(const char *file, t_rt *rt);
char				**tokenize(char *line);

/*					parse_scene.c				*/
int					parse_scene(t_parse *file, t_rt *rt);
int					parse_object(t_parse *file, t_rt *rt);
void				assign_bbox(t_obj *obj);
void				assign_bbox_translate(t_obj *obj, t_vec3 delta);
void				assign_rotation(t_obj *obj);

/*					parse_setup.c				*/
int					parse_ambient(char **tokens, t_parse *file,
						t_ambient *ambient);
int					parse_camera(char **tokens, t_parse *file,
						t_camera *camera);
int					parse_light(char **tokens, t_parse *file, t_light *light);

/*					parse_objects.c				*/
int					parse_plane(t_parse *file, t_obj *obj);
int					parse_sphere(t_parse *file, t_obj *obj);
int					parse_cylinder(t_parse *file, t_obj *obj);

/*					parse_utils.c				*/
bool				is_object(const char *token);
int					add_object(t_rt *rt, t_obj *obj);
int					count_tokens(char **tokens);
int					is_colour(t_parse *scene, char **col, t_col *colour);
int					is_vector(t_parse *scene, char **values, t_vec3 *vector,
						bool check_normal);
int					handle_parse_error(int fd, char *line, t_parse *file);

/*					parse_debug.c				*/
void				print_ambient(const t_ambient *ambient);
void				print_camera(const t_camera *camera);
void				print_light(const t_light *light);
void				print_obj(const t_obj *obj);

#endif