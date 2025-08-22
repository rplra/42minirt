/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:50:40 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/22 16:09:41 by rraja-az         ###   ########.fr       */
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
void	cleanup(t_rt *rt)
{
	if (!rt)
		return ;
	free_one(rt->obj);
	free_bvh(rt->bvh);
	if (rt->mlx)
		free_one(rt->mlx);
}

/* use this for linux */
/* void	cleanup(t_rt *rt)
{
	if (!rt)
	{
		return ;
	}
	free_main_img(rt);
	free_label_img(rt);
	free_info_img(rt);
	if (rt->mlx_win)
		mlx_destroy_window(rt->mlx, rt->mlx_win);
	free_bvh(rt->bvh);
	free_one(rt->obj);
	if (rt->mlx)
	{
		mlx_destroy_display(rt->mlx);
		free(rt->mlx);
	}
}  */

void	cleanup_and_exit(t_rt *rt, int exit_code)
{
	if (rt)
		cleanup(rt);
	exit(exit_code);
}
