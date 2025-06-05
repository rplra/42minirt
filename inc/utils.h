/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:42:28 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/05 10:32:48 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parse.h"

#ifndef UTILS_H
#define UTILS_H

# define ERROR_ARGFORMAT "Format: <./minirt> <scenes/scene.rt>"
# define ERROR_FILETYPE "Error: File type must be in .rt"
# define ERROR_FILEMOD "Error: File does not exist or has no read permission"
# define ERROR_FILEFD "Error: File not found"
# define ERROR_FILEEMPTY "Error: Empty file"
# define ERROR_PARAMEMPTY "Error: Parameter is empty"
# define ERROR_INVALIDID "Error: Invalid parameter ID"

# define ERROR_UNIQUEID "Error: A, C, L should be unique"
# define ERROR_MISSINGID "Error: Scene must at least have one A, C and L to render"
# define ERROR_RATIO "Error: Invalid ratio, range must be within 0.0 to 1.0"
# define ERROR_NORMAL "Error: Invalid vector normal"
# define ERROR_VECTOR "Error: Vector value must be -1 to 1"

# define ERROR_ACOUNT "Error: Invalid parameter count for Ambient"

# define ERROR_CCOUNT "Error: Invalid parameter count for Camera"
# define ERROR_CPOS "Error: Invalid camera position"
# define ERROR_CORT "Error: Invalid camera orientation"
# define ERROR_CFOV "Error: Camera FOV must be between 0 to 180"

# define ERROR_LCOUNT "Error: Invalid parameter count for Light"
# define ERROR_LPOS "Error: Invalid Light position"

# define ERROR_PLCOUNT "Error: Invalid parameter count for Plane"
# define ERROR_PLPOS "Error: Invalid Plane position"
# define ERROR_PLORT "Error: Invalid Plane orientation"

# define ERROR_SPCOUNT "Error: Invalid parameter count for Sphere"
# define ERROR_SPPOS "Error: Invalid Sphere position"
# define ERROR_SPDIA "Error: Sphere diameter must be a positive interger"

# define ERROR_CYCOUNT "Error: Invalid parameter count for Cylinder"
# define ERROR_CYPOS "Error: Invalid Cylinder position"
# define ERROR_CYDIA "Error: Cylinder diameter must be a positive interger"
# define ERROR_CYHT "Error: Cylinder height must be a positive interger"

# define ERROR_COLCOUNT "Error: Colour must consist of 3 values [R, G, B]"
# define ERROR_INVALID_R "Error: R value must be a positive integer [0 to 255]"
# define ERROR_INVALID_G "Error: G value must be a positive integer [0 to 255]"
# define ERROR_INVALID_B "Error: B value must be a positive integer [0 to 255]"
# define ERROR_INVALID_COL_VAL "Error: Colour values must be 0 to 255"

# define ERROR_INVALID_COORD "Error: Coordinate must consist of 3 values; x, y, z"
# define ERROR_INVALID_X "Error: Invalid x value"
# define ERROR_INVALID_Y "Error: Invalid y value"
# define ERROR_INVALID_Z "Error: Invalid z value"

int		print_error(t_parse *scene, char *msg, int param, char **params);
void	exit_with_error(char *msg);
void	perror_exit(char *perrmsg);

int		free_array(char **arr);
int		free_arrays(char **arr1, char **arr2, char **arr3, char **arr4);


#endif