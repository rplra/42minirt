/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:09:49 by hsim              #+#    #+#             */
/*   Updated: 2025/07/06 18:51:49 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_one(void *vars)
{
	if (!vars)
		return ;
	free(vars);
	vars = NULL;
}

void	free_assign_hsv(int **hsv, int free_count)
{
	if (!hsv)
		return ;
	while (free_count > 0)
	{
		free(hsv[--free_count]);
		hsv[free_count] = NULL;
	}
}

void	free_bvh(t_bvh_tree *bvh)
{
	if (!bvh)
		return ;
	if (bvh->l_type == BVH)
		free_bvh(bvh->left);
	if (bvh->r_type == BVH)
		free_bvh(bvh->right);
	free(bvh);
}

/* 
 * consolidate all mallocs and free when exit program
 * indicator controls what to free
 */
void	free_render(t_rt *vars, int indicator)
{
	if (!vars)
		return ;
	free_one(vars->mlx);
	free_bvh(vars->bvh);
	free_one(vars->obj);

	if (indicator > 0)
	{
		// free_one(vars->z_array);
		// free_assign_hsv(vars->hsv_array, 3);
	}
}

// void	ft_lstclear_obj(t_obj **lst)
// {
// 	t_obj	*temp;

// 	if (lst == NULL)
// 		return ;
// 	temp = *lst;
// 	while (*lst != NULL)
// 	{
// 		temp = (*lst)->next;
// 		free(*lst);
// 		*lst = temp;
// 	}
// 	*lst = NULL;
// }
