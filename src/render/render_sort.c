/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:36:01 by hsim              #+#    #+#             */
/*   Updated: 2025/07/10 09:00:18 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	copy_sphere(t_obj *dest, t_obj src)
{
	dest->type = src.type;
	dest->sph.pos = src.sph.pos;
	dest->sph.rad = src.sph.rad;
	dest->material.albedo = src.material.albedo;
	dest->material.type = src.material.type;
	dest->material.specular = src.material.specular;
	dest->material.reflect = src.material.reflect;
	dest->material.fuzz = src.material.fuzz;
	create_bbox(dest, dest->bbox);
}

void	copy_obj(t_obj *dest, t_obj src)
{
	if (src.type == SPHERE)
		copy_sphere(dest, src);
		// *dest = new_sphere(src.sph.pos, src.sph.rad, src.material.albedo, src.material.type);
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

/* 22 lines ok! */
/*
 * Child function in merge_sort
 * *arr[2] = double pointer to left & right array
 * *array = the original full length array
 */
void	merge_final(t_obj *arr[2], t_obj *res, int argc, bool (*func)(t_obj, t_obj))
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
			copy_obj(&res[i++], arr[L][l++]);
		else
			copy_obj(&res[i++], arr[R][r++]);
	}
	while (l < len[L] && i < argc)
		copy_obj(&res[i++], arr[L][l++]);
	while (r < len[R] && i < argc)
		copy_obj(&res[i++], arr[R][r++]);
}

/* 14 lines ok! */
/*
 * argc indicates the length of array
 * argc has to be argc -1 in here
 * returns result in int *array
 */
void	merge_sort(t_obj *res, int argc, bool (*func)(t_obj, t_obj))
{
	t_obj	*arr[2];
	int		mid;

	if (argc <= 1)
		return ;
	mid = (argc / 2);
	arr[L] = (t_obj *)malloc(sizeof(t_obj) * mid);
	arr[R] = (t_obj *)malloc(sizeof(t_obj) * (argc - mid));
	copy_array(arr[L], res, mid);
	copy_array(arr[R], &res[mid], (argc - mid));
	merge_sort(arr[L], mid, func);
	merge_sort(arr[R], argc - mid, func);
	merge_final(arr, res, argc, func);
	free_mergesort_ptr(arr, 2);
}
