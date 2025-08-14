/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:19:29 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 17:39:35 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_ambient(const t_ambient *ambient)
{
	printf("Ambient ratio: %f\n", ambient->intensity);
	printf("Ambient colour: (r=%f, g=%f, b=%f)\n", ambient->colour.R,
		ambient->colour.G, ambient->colour.B);
}

void	print_camera(const t_camera *camera)
{
	printf("Camera pos: (x=%f, y=%f, z=%f)\n", camera->pos.x, camera->pos.y,
		camera->pos.z);
	printf("Camera ort: (x=%f, y=%f, z=%f)\n", camera->vup.x, camera->vup.y,
		camera->vup.z);
	printf("Camera fov: %f\n", camera->hfov);
}

void	print_light(const t_light *light)
{
	printf("Light pos: (x=%f, y=%f, z=%f)\n", light->pos.x, light->pos.y,
		light->pos.z);
	printf("Light brightness: %f\n", light->brightness);
	printf("Light colour: (r=%f, g=%f, b=%f)\n", light->colour.R,
		light->colour.G, light->colour.B);
}
