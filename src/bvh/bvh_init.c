/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:27:52 by hsim              #+#    #+#             */
/*   Updated: 2025/08/14 17:29:12 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static
/*
 * child function in build_bvh_tree
 * assigns bvh_node to obj *
 */
static void	assign_bvh_node(t_bvh_tree *bvh, t_obj *obj, int id[2])
{
	// /*debug*/printf("return (%d~%d\n-------\n", id[0], id[1]));
	bvh->id[L] = id[0];
	bvh->type[L] = obj[0].type;
	bvh->left = &obj[0];
	if (id[1] - id[0] == 1)
	{
		bvh->id[R] = id[0];
		bvh->type[R] = obj[0].type;
		bvh->right = &obj[0];
	}
	else
	{
		bvh->id[R] = id[1] - 1;
		bvh->type[R] = obj[1].type;
		bvh->right = &obj[1];
	}
}

// static
/*
 * child function in sort_n_split
 * returns the axis where the difference between max-min is largest
 */
static int	longest_axis(t_interval bbox[3])
{
	int	n[3];

	n[X] = bbox[X].max - bbox[X].min;
	n[Y] = bbox[Y].max - bbox[Y].min;
	n[Z] = bbox[Z].max - bbox[Z].min;
	if (n[X] > n[Y] && n[X] > n[Z])
		return (X);
	else if (n[Y] > n[X] && n[Y] > n[Z])
		return (Y);
	return (Z);
}

// static
/*
 * child function in build_bvh_tree
 * sort,split list into half & call build_bvh_tree recursively
 */
static void	sort_n_split(t_bvh_tree *bvh, t_obj *obj, int id[2],
		bool (*func[3])(t_obj, t_obj))
{
	int	mid;
	int	axis;
	int	half[2];

	// /*debug*/printf("else\n");
	// mid = (argc / 2);
	mid = ((id[1] - id[0]) / 2);
	axis = longest_axis(bvh->bbox);
	// /*debug*/printf("merge_sort:%d id_dif:%d\n", argc, id[1] - id[0]);
	// merge_sort(obj, argc, func[axis]);
	merge_sort(obj, id[1] - id[0], func[axis]);
	bvh->type[L] = BVH;
	bvh->type[R] = BVH;
	bvh->id[L] = -1;
	bvh->id[R] = -1;
	half[0] = id[0];
	half[1] = id[0] + mid;
	// /*debug*/printf("|ac[L]: %d~%d %d\n", half[0], half[1], mid);
	bvh->left = build_bvh_tree(obj, half, func);
	/* ********************************************************* */
	half[0] = half[1];
	half[1] = id[1];
	// /*debug*/printf("|ac[R]: %d~%d, %d\n", half[0], half[1], argc-mid);
	bvh->right = build_bvh_tree(&obj[mid], half, func);
	// mid, argc-mid
}

t_bvh_tree	*build_bvh_tree(t_obj *obj, int id[2], bool (*func[3])(t_obj,
			t_obj))
{
	t_bvh_tree	*bvh;

	bvh = (t_bvh_tree *)malloc(sizeof(t_bvh_tree));
	// /*debug*/printf("_____build_tree_____\nac:%d %d\n", id[1] - id[0], argc);
	// /*debug*/debug_print_bbox("obj[0]", obj[0].bbox);
	get_bbox_val(obj, id[1] - id[0], bvh->bbox);
	// /*debug*/debug_print_bbox("fin_box", bvh->bbox);
	// /*debug*/printf("\n");
	if (id[1] - id[0] <= 0)
		return (NULL);
	if ((id[1] - id[0] == 1) || (id[1] - id[0] == 2))
		assign_bvh_node(bvh, obj, id);
	else
		sort_n_split(bvh, obj, id, func);
	return (bvh);
}

/* build a bvh tree with objects list */
void	init_bvh_node(t_rt *vars)
{
	int		id[2];

	bool (*box_compare[3])(t_obj, t_obj);
	init_box_compare(box_compare);
	id[0] = 0;
	id[1] = vars->obj_count;
	vars->bvh = build_bvh_tree(vars->obj, id, box_compare);
}
