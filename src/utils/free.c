/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:50:40 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/19 04:49:16 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	free_array(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return (1);
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (0);
}

/* frees a single block of memory */
void	free_one(void *vars)
{
	if (!vars)
		return ;
	free(vars);
	vars = NULL;
}

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

/* use this for mac */
// void	cleanup(t_rt *rt)
// {
// 	if (!rt)
// 		return ;
// 	free_one(rt->mlx);
// 	free_bvh(rt->bvh);
// 	free_one(rt->obj);
// }

/* use this for linux */
void cleanup(t_rt *rt)
{
    if (!rt)
        return;
    if (rt->img.img)
        mlx_destroy_image(rt->mlx, rt->img.img);
    if (rt->mlx_win)
        mlx_destroy_window(rt->mlx, rt->mlx_win);
    free_bvh(rt->bvh);
    free_one(rt->obj);
	if (rt->mlx)
	{
		mlx_destroy_display(rt->mlx); // LINUX ONLY
		free(rt->mlx);
	}
}


void	cleanup_and_exit(t_rt *rt, int exit_code)
{
	if (rt)
		cleanup(rt);
	exit(exit_code);
}

// /* 
//  * consolidate all mallocs and free when exit program
//  * indicator controls what to free
//  * brief: free all resources used by renderer
//  */
// void	free_render(t_rt *rt, int indicator)
// {
// 	if (!rt)
// 		return ;
// 	free_one(rt->mlx);
// 	free_bvh(rt->bvh);
// 	free_one(rt->obj);

// 	if (indicator > 0)
// 	{
// 		//add custom controls here
// 	}
// }

/* void	cleanup(t_rt *rt)
{
	if (rt->obj)
	{
		free(rt->obj);
		rt->obj = NULL;
		rt->obj_count = 0;
	}
	if (rt->bvh)
	{
		free_bvh(rt->bvh);
		rt->bvh = NULL;
	} 
} */
