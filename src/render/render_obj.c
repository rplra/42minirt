/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:13:15 by hsim              #+#    #+#             */
/*   Updated: 2025/06/27 22:27:21 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


/*
 * wrapper function to assign members in target to location & sph_radius
 * target has been malloced before passing to here
 */
// t_sph	*new_sphere(void *param)
// {
// 	t_sph	*target;
// 	t_sph	*input;

// 	input = (t_sph *)param;
// 	target = (t_sph *)malloc(sizeof(t_sph));
// 	target->orig = input->orig;
// 	target->rad = input->rad;
// 	target->mat.albedo = input->mat.albedo;
// 	target->mat.type = input->mat.type;
// 	return (target);
// }


t_sph	new_sphere(t_vec3 position, float sph_radius, t_vec3 color, t_uchar mat_type)
{
	t_sph	target;

	target.orig = position;
	target.rad = sph_radius;
	target.mat.albedo = color;
	target.mat.type = mat_type;
	return (target);
}

/* mallocs a new sphere */
t_obj	*new_sph(t_vec3 position, float sph_radius, \
t_vec3 color, t_uchar mat_type)
{
	t_obj	*res;

	res = (t_obj *)malloc(sizeof(t_obj));
	if (!res)
		return (NULL);
	res->type = SPHERE;
	res->sph.orig = position;
	res->sph.rad = sph_radius;
	res->sph.mat.type = mat_type;
	res->sph.mat.albedo = color;
	res->next = NULL;
	// res->mat.type = mat_type;
	// res->mat.albedo = color;
	return (res);
}

t_obj	*ft_lstlast_obj(t_obj *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}


/* adds obj to end of lst */
void	new_obj(t_rt *vars, t_obj **lst, t_obj *new)
{
	t_obj		*tmp;
	t_interval	bound_box[3];

	if (!new || !vars)
		return ;
	tmp = ft_lstlast_obj(*lst);
	if (tmp == NULL)
		*lst = new;
	else
		tmp->next = new;
	get_bbox(new->type, new, bound_box);
	update_aabb_box(vars->bbox, bound_box, vars->bbox);
}
