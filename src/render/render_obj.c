/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:13:15 by hsim              #+#    #+#             */
/*   Updated: 2025/07/09 20:53:45 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_sph	new_sphere(t_vec3 position, float sph_radius, t_vec3 color, t_uchar mat_type)
// {
// 	t_sph	target;

// 	target.orig = position;
// 	target.rad = sph_radius;
// 	target.mat.albedo = color;
// 	target.mat.type = mat_type;
// 	return (target);
// }

t_obj	new_sphere(t_vec3 position, float sph_radius, t_vec3 color, t_uchar mat_type)
{
	t_obj	target;

	target.type = SPHERE;
	target.sph.pos = position;
	target.sph.rad = sph_radius;
	target.mat.albedo = color;
	target.mat.type = mat_type;
	create_bbox(&target, target.bbox);
	return (target);
}

/*
 * returns obj function that returns a malloc-ed pointer
 * for specified obj_type
 */
void	init_new_obj_func2(t_obj (*add_obj[])(t_vec3, float, t_vec3, t_uchar))
{
	add_obj[SPHERE] = new_sphere;
}

// void	new_obj(t_rt *vars, t_obj **lst, t_obj *new)
// {
// 	t_obj		*tmp;
// 	t_interval	bound_box[3];

// 	if (!new || !vars)
// 		return ;
// 	tmp = ft_lstlast_obj(*lst);
// 	if (tmp == NULL)
// 		*lst = new;
// 	else
// 		tmp->next = new;
// 	get_bbox(new, bound_box);
// 	update_aabb_box(vars->bbox, bound_box, vars->bbox);

// 	// /*debug*/printf("bbox_x: %f %f, bbox_y: %f %f, bbox_z: %f %f\n", vars->bbox[X].min, vars->bbox[X].max, \
// // vars->bbox[Y].min, vars->bbox[Y].max, vars->bbox[Z].min, vars->bbox[Z].max);
// }

/* ****************************************************** */

/* mallocs a new sphere */
// t_obj	*new_sph(t_vec3 position, float sph_radius, \
// t_vec3 color, t_uchar mat_type)
// {
// 	t_obj	*res;

// 	res = (t_obj *)malloc(sizeof(t_obj));
// 	if (!res)
// 		return (NULL);
// 	res->type = SPHERE;
// 	res->sph.orig = position;
// 	res->sph.rad = sph_radius;
// 	res->mat.type = mat_type;
// 	res->mat.albedo = color;

// 	res->next = NULL;
// 	return (res);
// }

/*
 * returns obj function that returns a malloc-ed pointer
 * for specified obj_type
 */
// void	init_new_obj_func(t_obj *(*add_obj[])(t_vec3, float, t_vec3, t_uchar))
// {
// 	add_obj[SPHERE] = new_sph;
// }

/* adds obj to end of lst */
// void	new_obj(t_rt *vars, t_obj **lst, t_obj *new)
// {
// 	t_obj		*tmp;
// 	t_interval	bound_box[3];

// 	if (!new || !vars)
// 		return ;
// 	tmp = ft_lstlast_obj(*lst);
// 	if (tmp == NULL)
// 		*lst = new;
// 	else
// 		tmp->next = new;
// 	get_bbox(new, bound_box);
// 	update_aabb_box(vars->bbox, bound_box, vars->bbox);

// 	// /*debug*/printf("bbox_x: %f %f, bbox_y: %f %f, bbox_z: %f %f\n", vars->bbox[X].min, vars->bbox[X].max, \
// // vars->bbox[Y].min, vars->bbox[Y].max, vars->bbox[Z].min, vars->bbox[Z].max);
// }
