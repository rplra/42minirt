/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:36:01 by hsim              #+#    #+#             */
/*   Updated: 2025/08/07 21:23:20 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	dest->cyl.pos = src.cyl.pos;
	dest->cyl.axis = src.cyl.axis;
	dest->cyl.rad = src.cyl.rad;
	dest->cyl.height = src.cyl.height;
	dest->cyl.coord[X] = src.cyl.coord[X];
	dest->cyl.coord[Y] = src.cyl.coord[Y];
	dest->cyl.d[0] = src.cyl.d[0];
	dest->cyl.d[1] = src.cyl.d[1];
	dest->cyl.w = src.cyl.w;
	dest->cyl.axis_height = src.cyl.axis_height;
}


void	init_copy_func(void (*copy[3])(t_obj *, t_obj))
{
	copy[SPHERE] = copy_sph;
	copy[PLANE] = copy_plane;
	copy[CYLINDER] = copy_cyl;
}

void	copy_bbox(t_interval dest[3], t_interval src[3])
{
	dest[X].min = src[X].min;
	dest[X].max = src[X].max;
	dest[Y].min = src[Y].min;
	dest[Y].max = src[Y].max;
	dest[Z].min = src[Z].min;
	dest[Z].max = src[Z].max;
}

void	copy_obj(t_obj *dest, t_obj src)
{
	void	(*copy[3])(t_obj *, t_obj);

	dest->id = src.id;
	dest->type = src.type;
	dest->material.albedo = src.material.albedo;
	dest->material.type = src.material.type;
	dest->material.specular = src.material.specular;
	dest->material.reflect = src.material.reflect;
	dest->material.fuzz = src.material.fuzz;
	dest->bbox_center = src.bbox_center;
	dest->b_rotate = src.b_rotate;
	dest->rotate = src.rotate;

	init_copy_func(copy);
	copy[src.type](dest, src);

	copy_bbox(dest->bbox, src.bbox);
	copy_bbox(dest->bbox_ori, src.bbox_ori);
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
