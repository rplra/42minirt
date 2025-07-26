/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:36:01 by hsim              #+#    #+#             */
/*   Updated: 2025/07/19 17:24:46 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// brief; backbone of sorting and copying scene objects

void	copy_sph(t_obj *dest, t_obj src)
{
	dest->sph.pos = src.sph.pos;
	dest->sph.rad = src.sph.rad;
}

void	copy_plane(t_obj *dest, t_obj src)
{
	dest->plane.pos = src.plane.pos;
	dest->plane.coord[X] = src.plane.coord[X];
	dest->plane.coord[Y] = src.plane.coord[Y];
	dest->plane.normal = src.plane.normal;
	dest->plane.d = src.plane.d;
	dest->plane.w = src.plane.w;
}

void	copy_cyl(t_obj *dest, t_obj src)
{
	(void) dest;
	(void) src;
}


void	init_copy_func(void (*copy[3])(t_obj *, t_obj))
{
	copy[SPHERE] = copy_sph;
	copy[PLANE] = copy_plane;
	copy[CYLINDER] = copy_cyl;
}

/*
 * copies all data from t_obj
 * used when duplicating objects during sorting and building new arrays
 * recalculates bounding box for copied object
 */
void	copy_obj(t_obj *dest, t_obj src)
{
	void	(*copy[3])(t_obj *, t_obj);

	dest->type = src.type;
	dest->material.albedo = src.material.albedo;
	dest->material.type = src.material.type;
	dest->material.specular = src.material.specular;
	dest->material.reflect = src.material.reflect;
	dest->material.fuzz = src.material.fuzz;

	init_copy_func(copy);
	copy[src.type](dest, src);
	create_bbox(dest, dest->bbox);
}

/* used in sorting and merging, where we need to duplicate arrays of objects */
void	copy_array(t_obj *dest, t_obj *src, int n)
{
	while (--n >= 0)
		copy_obj(&dest[n], src[n]);
}

/* free temp array used for merge sort */
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
 * 
 */
void	merge_final(t_obj *arr[2], t_obj *dest, int argc, bool (*func)(t_obj, t_obj))
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

/* 14 lines ok! */
/*
 * brief: recursively sorts an array of obj struct using merge sort
 * argc indicates the length of array
 * argc has to be argc -1 in here
 * returns result in int *array
 * 
 * 1. find midpoint
 * 2. copy first and second into dest
 * 3. recursively sort the first half, then sort the second half
 * 4. merge 2 sorted halves into dest using func
 * 5. free temp pointer 
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
