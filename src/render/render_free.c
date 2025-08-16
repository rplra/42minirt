/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:09:49 by hsim              #+#    #+#             */
/*   Updated: 2025/08/15 09:13:04 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* frees a single block of memory */
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

/* frees all nodes in BVH */
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
 * brief: free all resources used by renderer
 */
void	free_render(t_rt *rt, int indicator)
{
	if (!rt)
		return ;
	free_one(rt->mlx);
	free_bvh(rt->bvh);
	free_one(rt->obj);

	if (indicator > 0)
	{
		//add custom controls here
	}
}
