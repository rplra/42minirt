/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:36:01 by hsim              #+#    #+#             */
/*   Updated: 2025/08/22 08:46:04 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	copy_bbox(t_interval dest[3], t_interval src[3])
{
	dest[X].min = src[X].min;
	dest[X].max = src[X].max;
	dest[Y].min = src[Y].min;
	dest[Y].max = src[Y].max;
	dest[Z].min = src[Z].min;
	dest[Z].max = src[Z].max;
}

void	copy_array(t_obj *dest, t_obj *src, int n)
{
	while (--n >= 0)
		copy_obj(&dest[n], src[n]);
}

void	free_mergesort_ptr(t_obj *ptr[2], int n)
{
	while (n > 0)
		free(ptr[--n]);
}

/*
 * Child function in merge_sort
 * *arr[2] = double pointer to left & right array
 * *array = the original full length array
 */
void	merge_final(t_obj *arr[2], t_obj *dest, int argc, bool (*func)(t_obj,
			t_obj))
{
	int	i;
	int	l;
	int	r;
	int	len[2];

	i = 0;
	l = 0;
	r = 0;
	len[L] = (argc / 2);
	len[R] = (argc - len[L]);
	while (l < len[L] && r < len[R] && i < argc)
	{
		if (func(arr[L][l], arr[R][r]))
			copy_obj(&dest[i++], arr[L][l++]);
		else
			copy_obj(&dest[i++], arr[R][r++]);
	}
	while (l < len[L] && i < argc)
		copy_obj(&dest[i++], arr[L][l++]);
	while (r < len[R] && i < argc)
		copy_obj(&dest[i++], arr[R][r++]);
}

/*
 * argc indicates the length of array
 * argc has to be argc -1 in here
 * returns result in int *array
 */
void	merge_sort(t_obj *dest, int argc, bool (*func)(t_obj, t_obj))
{
	t_obj	*arr[2];
	int		mid;

	if (argc <= 1)
		return ;
	mid = (argc / 2);
	arr[L] = (t_obj *)malloc(sizeof(t_obj) * mid);
	arr[R] = (t_obj *)malloc(sizeof(t_obj) * (argc - mid));
	copy_array(arr[L], dest, mid);
	copy_array(arr[R], &dest[mid], (argc - mid));
	merge_sort(arr[L], mid, func);
	merge_sort(arr[R], argc - mid, func);
	merge_final(arr, dest, argc, func);
	free_mergesort_ptr(arr, 2);
}
