/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:42:28 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/13 11:21:56 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parse.h"

#ifndef UTILS_H
#define UTILS_H

# define ERROR_ARGFORMAT "Format: <./minirt> <scenes/scene.rt>"
# define ERROR_FILETYPE "File type must be in .rt"
# define ERROR_FILEMOD "File does not exist or has no read permission"
# define ERROR_FILEFD "File not found"
# define ERROR_FILEEMPTY "Empty file"
# define ERROR_PARAMEMPTY "Parameter is empty"
# define ERROR_INVALIDID "Invalid parameter ID"

# define ERROR_UNIQUEID "A, C, L should be unique"
# define ERROR_MISSINGID "Scene must at least have one A, C and L to render"
# define ERROR_RATIO "Invalid ratio, range must be within 0.0 to 1.0"
# define ERROR_NORMAL "Invalid vector normal"
# define ERROR_VECTOR "Vector value must be -1 to 1"

# define ERROR_ACOUNT "Invalid parameter count for Ambient"

# define ERROR_CCOUNT "Invalid parameter count for Camera"
# define ERROR_CPOS "Invalid camera position"
# define ERROR_CORT "Invalid camera orientation"
# define ERROR_CFOV "Camera FOV must be between 0 to 180"

# define ERROR_LCOUNT "Invalid parameter count for Light"
# define ERROR_LPOS "Invalid Light position"

# define ERROR_PLCOUNT "Invalid parameter count for Plane"
# define ERROR_PLPOS "Invalid Plane position"
# define ERROR_PLORT "Invalid Plane orientation"

# define ERROR_SPCOUNT "Invalid parameter count for Sphere"
# define ERROR_SPPOS "Invalid Sphere position"
# define ERROR_SPDIA "Sphere diameter must be a positive interger"

# define ERROR_CYCOUNT "Invalid parameter count for Cylinder"
# define ERROR_CYPOS "Invalid Cylinder position"
# define ERROR_CYDIA "Cylinder diameter must be a positive interger"
# define ERROR_CYHT "Cylinder height must be a positive interger"

# define ERROR_COLCOUNT "Colour must consist of 3 values [R, G, B]"
# define ERROR_INVALID_R "R value must be a positive integer [0 to 255]"
# define ERROR_INVALID_G "G value must be a positive integer [0 to 255]"
# define ERROR_INVALID_B "B value must be a positive integer [0 to 255]"
# define ERROR_INVALID_COL_VAL "Colour values must be 0 to 255"

# define ERROR_INVALID_COORD "Coordinate must consist of 3 values; x, y, z"
# define ERROR_INVALID_X "Invalid x value"
# define ERROR_INVALID_Y "Invalid y value"
# define ERROR_INVALID_Z "Invalid z value"

int		print_error(t_parse *file, char *msg, int param, char **params);
void	exit_with_error(char *msg);
void	perror_exit(char *perrmsg);

int		free_array(char **arr);
int		free_arrays(char **arr1, char **arr2, char **arr3, char **arr4);
void	free_scene(t_scene *scene);
void	cleanup_and_exit(t_scene *scene);

void	flush_gnl(int fd);

#endif