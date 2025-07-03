/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:13:15 by hsim              #+#    #+#             */
/*   Updated: 2025/07/03 13:48:20 by rraja-az         ###   ########.fr       */
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

// t_obj	*ft_lstlast_obj(t_obj *lst)
// {
// 	if (lst == NULL)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
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
// 	get_bbox(new->type, new, bound_box);
// 	update_aabb_box(vars->bbox, bound_box, vars->bbox);

// 	/*debug*/printf("bbox_x: %f %f, bbox_y: %f %f, bbox_z: %f %f\n", vars->bbox[X].min, vars->bbox[X].max, \
// vars->bbox[Y].min, vars->bbox[Y].max, vars->bbox[Z].min, vars->bbox[Z].max);
// }
