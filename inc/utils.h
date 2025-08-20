/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:42:28 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/20 08:18:40 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minirt.h"
# include "parse.h"

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

int			print_error(t_parse *file, char *msg, int param, char **params);
void		exit_with_error(char *msg);
void		perror_exit(char *perrmsg);

void		free_main_img(t_rt *rt);
void		free_label_img(t_rt *rt);
void		free_info_img(t_rt *rt);

int			free_array(char **arr);
void		free_one(void *vars);
void		free_bvh(t_bvh_tree *bvh);
void		cleanup(t_rt *rt);
void		cleanup_and_exit(t_rt *rt, int exit_code);



#endif