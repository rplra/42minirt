/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:21:45 by hsim              #+#    #+#             */
/*   Updated: 2025/07/04 19:30:09 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
 * update to add new at end of lst
 * lst need to passed as &lst
 */
// void	obj_add_back(t_obj **lst, t_obj *new)
// {
// 	t_obj	*tmp;

// 	tmp = ft_lstlast_obj(*lst);
// 	if (tmp == NULL)
// 		*lst = new;
// 	else
// 		tmp->next = new;
// }

// t_obj	*ft_lstnew_obj(t_obj *lst)
// {
// 	t_obj	*res;
// 	t_obj	*(*add_obj[3])(t_vec3, float, t_vec3, t_uchar);

// 	res = NULL;
// 	init_new_obj_func(add_obj);
// 	if (lst->type == SPHERE)
// 		res = add_obj[SPHERE](lst->sph.orig, lst->sph.rad, lst->mat.albedo, lst->mat.type);
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

// /* move forward by n number of list */
// t_obj	*ft_lst_forward(t_obj *obj, size_t n)
// {
// 	t_obj	*ptr;

// 	ptr = obj;
// 	while (n-- > 0 && ptr)
// 		ptr = ptr->next;
// 	return (ptr);
// }

// int	ft_lstsize_obj(t_obj *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (lst)
// 	{
// 		lst = lst->next;
// 		i++;
// 	}
// 	return (i);
// }