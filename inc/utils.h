/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:42:28 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/02 08:57:30 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parse.h"

#ifndef UTILS_H
#define UTILS_H

// Forward declaration for conversion functions
struct s_rt;
typedef struct s_rt t_rt;

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

# define ERROR_CCOUNT "Camera params must be 4 [C, coords, orientation, FOV]"
# define ERROR_CPOS "Invalid camera position"
# define ERROR_CORT "Invalid camera orientation"
# define ERROR_CFOV "Camera FOV must be between 0 to 180"

# define ERROR_LCOUNT "Light params must be 4 [L, coords, brightness, colour]"
# define ERROR_LPOS "Invalid Light position"

# define ERROR_PLCOUNT "Plane params must be 4 [pl, coords, normal, colour]"
# define ERROR_PLPOS "Invalid Plane position"
# define ERROR_PLORT "Invalid Plane orientation"

# define ERROR_SPCOUNT "Sphere params must be 4 [sp, coords, diameter, colour]"
# define ERROR_SPPOS "Invalid Sphere position"
# define ERROR_SPDIA "Sphere diameter must be a positive interger"

# define ERROR_CYCOUNT "Cylinder params must be 6 [cy, coords, axis, diameter, height, colour]"
# define ERROR_CYPOS "Invalid Cylinder position"
# define ERROR_CYDIA "Cylinder diameter must be a positive interger"
# define ERROR_CYHT "Cylinder height must be a positive interger"

# define ERROR_COLCOUNT "Colour must consist of 3 values [R, G, B]"
# define ERROR_INVALID_R "R colour value must be a positive integer [0 to 255]"
# define ERROR_INVALID_G "G colour value must be a positive integer [0 to 255]"
# define ERROR_INVALID_B "B colour value must be a positive integer [0 to 255]"
# define ERROR_INVALID_COL_VAL "Colour values must be 0 to 255"

# define ERROR_INVALID_COORD "Coordinate must consist of 3 values; x, y, z"
# define ERROR_INVALID_X "X value must be an integer"
# define ERROR_INVALID_Y "Y value must be an integer"
# define ERROR_INVALID_Z "Z value must be an integer"

int		print_error(t_parse *file, char *msg, int param, char **params);
void	exit_with_error(char *msg);
void	perror_exit(char *perrmsg);

int		free_array(char **arr);
int		free_arrays(char **arr1, char **arr2, char **arr3, char **arr4);
void	free_scene(t_scene *scene);
void	cleanup_and_exit(t_scene *scene);

void	flush_gnl(int fd);
float	clamp(float value, float min, float max);
t_colour	colour_clamp(t_colour c);

// Conversion functions
t_vec3	colour_to_vec3(t_colour colour);
t_colour	vec3_to_colour(t_vec3 vec);
void	convert_scene_to_render(t_scene *scene, t_rt *rt);
void	convert_camera(t_scene *scene, t_rt *rt);
void	convert_objects(t_scene *scene, t_rt *rt);
void	convert_ambient(t_scene *scene, t_rt *rt);

#endif