/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:13:15 by hsim              #+#    #+#             */
/*   Updated: 2025/06/27 15:27:30 by hsim             ###   ########.fr       */
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
// t_obj	*new_sphere(t_vec3 position, float sph_radius, \
// t_vec3 color, t_uchar mat_type)
// {
// 	t_obj	*res;

// 	res = malloc(sizeof(t_obj));
// 	if (!res)
// 		return (NULL);
// 	res->is->sph.mat.type = mat_type;
// 	res->is->sph.mat.albedo = color;
// 	res->is->sph.orig = position;
// 	res->is->sph.rad = sph_radius;
// }

// t_obj	*ft_lstlast_rt(t_obj *lst)
// {
// 	if (lst == NULL)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }


// /* adds obj to end of lst */
// void	add_obj_back(t_obj **lst, t_obj *new)
// {
// 	t_obj	*tmp;

// 	tmp = ft_lstlast_rt(*lst);
// 	if (tmp == NULL)
// 		*lst = new;
// 	else
// 		tmp->next = new;
// }
