/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:50:40 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/03 14:56:25 by rraja-az         ###   ########.fr       */
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

int	free_arrays(char **arr1, char **arr2, char **arr3, char **arr4)
{
	free_array(arr1);
	free_array(arr2);
	free_array(arr3);
	free_array(arr4);
	return (0);
}

void	free_scene(t_rt *rt)
{
	if (rt->obj)
	{
		free(rt->obj);
		rt->obj = NULL;
		rt->obj_count = 0;
	}
}

void	cleanup_and_exit(t_rt *rt)
{
	if (rt)
		free_scene(rt);
	exit(1);
}