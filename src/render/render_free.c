/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:09:49 by hsim              #+#    #+#             */
/*   Updated: 2025/07/11 17:14:27 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// frees a single block of memory
void	free_one(void *vars)
{
	if (!vars)
		return ;
	free(vars);
	vars = NULL;
}

// void	free_assign_hsv(int **hsv, int free_count)
// {
// 	if (!hsv)
// 		return ;
// 	while (free_count > 0)
// 	{
// 		free(hsv[--free_count]);
// 		hsv[free_count] = NULL;
// 	}
// }

// frees all nodes in BVH
void	free_bvh(t_bvh_tree *bvh)
{
	if (!bvh)
		return ;
	if (bvh->type[L] == BVH)
		free_bvh(bvh->left);
	if (bvh->type[R] == BVH)
		free_bvh(bvh->right);
	free(bvh);
}

/* 
 * consolidate all mallocs and free when exit program
 * indicator controls what to free
 */
// free all resources used by renderer
void	free_render(t_rt *vars, int indicator)
{
	if (!vars)
		return ;
	free_one(vars->mlx);
	free_bvh(vars->bvh);
	free_one(vars->obj);

	if (indicator > 0)
	{
		//add custom controls here
	}
}

/*
void	ft_lstclear_obj(t_obj **lst)
{
	t_obj	*temp;

	if (lst == NULL)
		return ;
	temp = *lst;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
*/
