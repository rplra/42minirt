/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init-bvh.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:27:52 by hsim              #+#    #+#             */
/*   Updated: 2025/07/14 21:47:14 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//static
/*
 * child function in build_bvh_tree
 * assigns bvh_node to obj *
 */
// assigns object to the left and right children of BVH node 
// only used when there are only 1 or 2 objects left in a group (the leaf case)
static void	assign_bvh_node(t_bvh_tree *bvh, t_obj *obj, int id[2])
{
	/*debug*/printf("return %d~%d\n-------\n", id[0], id[1]);
	bvh->id[L] = id[0];				// set left child id
	bvh->type[L] = obj[0].type;		// set left child type (pl, sp, cy)
	bvh->left = &obj[0];			// set left child pointer
	if (id[1] - id[0] == 1)			// if there's only 1 obj in group
	{
		bvh->id[R] = id[0];			// right child is being set similarly to the left child
		bvh->type[R] = obj[0].type;	// both points to the same obj
		bvh->right = &obj[0];		// where group cannot be split further
	}
	else							// if there's 2 obj in the group
	{
		bvh->id[R] = id[1] - 1;		// id is set to the second index in range
		bvh->type[R] = obj[1].type;
		bvh->right = &obj[1];
	}
}

// static
/*
 * child function in sort_n_split
 * returns the axis where the difference between max-min is largest
 */
// find the longest axis if bounding box
// when we split obj to build bvh, we split along the widest group, so tree is balanced
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

//static
/*
 * child function in build_bvh_tree
 * sort,split list into half & call build_bvh_tree recursively
 */
// split a group into half along longest axis, sorts them and recursive build the left and right BVH subtrees
// core of BVH building, keeps splitting only left last 1 or 2 (assign_bvh_node)
static void	sort_n_split(t_bvh_tree *bvh, t_obj *obj, \
int id[2], bool (*func[3])(t_obj, t_obj))
{
	int	mid;
	int	axis;
	int	half[2];

	/*debug*/printf("else\n");
	// mid = (argc / 2);
	mid = ((id[1] - id[0]) / 2);						// calc midpoint
	axis = longest_axis(bvh->bbox);						// get the longest axis to split along
	// /*debug*/printf("merge_sort:%d id_dif:%d\n", argc, id[1] - id[0]);
	// merge_sort(obj, argc, func[axis]);
	merge_sort(obj, id[1] - id[0], func[axis]);			// sorts object along that axis
	bvh->type[L] = BVH;									// marks node as BVH type
	bvh->type[R] = BVH;
	bvh->id[L] = -1;									// signals that these are not objs
	bvh->id[R] = -1;									// when we see -1, we need to go deeper since it's pointing to bvh node instead of obj

	half[0] = id[0];									// setting up the left child range (handle first half of objs)
	half[1] = id[0] + mid;								// if id[0] = 0, id[1] = 4, and mid = 2, then: half[0] = 0, half[1] = 2

	/*debug*/printf("|ac[L]: %d~%d %d\n", half[0], half[1], mid);
	bvh->left = build_bvh_tree(obj, half, func);		// build the left subtree
	/* ********************************************************* */
	half[0] = half[1];									// set up the right child range
	half[1] = id[1];									// after the left, half[0] = 2, half[1] = 4
	// /*debug*/printf("|ac[R]: %d~%d, %d\n", half[0], half[1], argc-mid);
	bvh->right = build_bvh_tree(&obj[mid], half, func);	// recursively build the left and right subtrees
	// mid, argc-mid
}

// recursively build the bvh tree for a group of projects
t_bvh_tree	*build_bvh_tree(t_obj *obj, int id[2], bool (*func[3])(t_obj, t_obj))
{
	t_bvh_tree	*bvh;

	bvh = (t_bvh_tree *)malloc(sizeof(t_bvh_tree));		// alloc new bvh node
	// /*debug*/printf("_____build_tree_____\nac:%d %d\n", id[1] - id[0], argc);
	// /*debug*/debug_print_bbox("obj[0]", obj[0].bbox);

	get_bbox_val(obj, id[1] - id[0], bvh->bbox);		// calc bb for current group of obj
	/*debug*/debug_print_bbox("fin_box", bvh->bbox);
	/*debug*/printf("\n");
	if (id[1] - id[0] <= 0)								// if there are no obj, return null
		return (NULL);
	if ((id[1] - id[0] == 1) || (id[1] - id[0] == 2))	// if there are 1 / 2 obj
		assign_bvh_node(bvh, obj, id);					// assign them as leaves
	else									
		sort_n_split(bvh, obj, id, func);				// else splits the group and recurses
	return (bvh);										// return root of bhv subtree
}

/* build a bvh tree with objects list */
// entry point for building the bvh tree for the whole scene
// called during init var
void	init_bvh_node(t_rt *vars)		
{
	int	id[2];								// array id, obj range

	bool (*box_compare[3])(t_obj, t_obj);	// declare funct pointer arrays
	init_box_compare(box_compare);			// init box compare (sort obj along longest bb axis)
	id[0] = 0;								// start of obj
	id[1] = vars->obj_count;				// end of obj total number
	vars->bvh = build_bvh_tree(\			// build the tree
vars->obj, id, box_compare);
}
